#include "Mesh.h"
#include "Vertex.h"
#include "MeshSegment.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Light.h"

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "glm/ext/matrix_transform.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/mat4x4.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/transform.hpp"

Mesh::~Mesh()
{
	delete m_material;
	delete m_shader;
}

void Mesh::Draw(glm::mat4 vpMatrix, glm::vec3 cameraPos) const
{
	for (MeshSegment* segment : m_segments) {

		if (m_material) {
			m_material->Apply(m_shader);
		}

		glm::mat4 modelMat = glm::translate(position) * glm::mat4(glm::quat(glm::radians(rotation))) * glm::scale(scale);
		glm::mat4 mvpMat = vpMatrix * modelMat;

		m_shader->BindUniform("mvpMat", mvpMat);
		m_shader->BindUniform("modelMat", modelMat);
		m_shader->BindUniform("viewPos", cameraPos);

		if (!lights.empty()) {
			m_shader->BindPointLightArray(lights);
			m_shader->BindDirectionalLight(dynamic_cast<DirLight*>(lights[0]));
		}

		segment->Bind();
		segment->Draw();
		segment->Unbind();
	}
}

void Mesh::LoadFromFile(const char* filePath)
{
	Assimp::Importer mesh_importer;

	const aiScene* scene = mesh_importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded | aiProcess_CalcTangentSpace);

	if (!scene) return;

	//read over each mesh and add them to the scene
	for (unsigned int mesh_index = 0; mesh_index < scene->mNumMeshes; ++mesh_index) {

		//initialise std::vectors
		std::vector<unsigned int> indices;
		std::vector<Vertex> vertices;

		//new mesh from scene 
		auto meshPointer = scene->mMeshes[mesh_index];

		//vertices | position, normal, texture coord
		for (unsigned int vx_ix = 0; vx_ix < meshPointer->mNumFaces; ++vx_ix) {

			for (int vI = 0; vI < 3; ++vI) {

				int index = meshPointer->mFaces[vx_ix].mIndices[vI];

				//Read the vertex data and add to vertex buffer
				Vertex vert = Vertex();

				vert.position.x = meshPointer->mVertices[index].x;
				vert.position.y = meshPointer->mVertices[index].y;
				vert.position.z = meshPointer->mVertices[index].z;

				if (meshPointer->HasNormals()) {
					vert.normal.x = meshPointer->mNormals[index].x;
					vert.normal.y = meshPointer->mNormals[index].y;
					vert.normal.z = meshPointer->mNormals[index].z;
				}

				if (meshPointer->mTextureCoords[0] != NULL) {
					vert.uv.x = meshPointer->mTextureCoords[0][index].x;
					vert.uv.y = meshPointer->mTextureCoords[0][index].y;
				}

				if (meshPointer->HasTangentsAndBitangents()) {
					vert.tangent.x = meshPointer->mTangents[index].x;
					vert.tangent.y = meshPointer->mTangents[index].y;
					vert.tangent.z = meshPointer->mTangents[index].z;
					
					vert.bitangent.x = meshPointer->mBitangents[index].x;
					vert.bitangent.y = meshPointer->mBitangents[index].y;
					vert.bitangent.z = meshPointer->mBitangents[index].y;
				}

				vertices.push_back(vert);
			}
		}

		AddSegment(new MeshSegment(vertices, indices));
	}
}

void Mesh::AddSegment(MeshSegment* mesh)
{
	m_segments.push_back(mesh);
}
