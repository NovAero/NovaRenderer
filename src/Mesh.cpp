#include "Mesh.h"
#include "Vertex.h"
#include "MeshSegment.h"
#include "Material.h"
#include "ShaderProgram.h"

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

Mesh::~Mesh()
{

}

void Mesh::Draw(glm::mat4 vpMatrix) const
{
	for (MeshSegment* segment : m_segments) {
		m_texture->Bind("albedoMap", m_shader);

		glm::mat4 modelMat = glm::scale(glm::mat4(1), scale);
		modelMat = glm::rotate(modelMat, rotation.x, glm::vec3(1, 0, 0));
		modelMat = glm::rotate(modelMat, rotation.y, glm::vec3(0, 1, 0));
		modelMat = glm::rotate(modelMat, rotation.z, glm::vec3(0, 0, 1));

		modelMat = glm::translate(modelMat, position);

		glm::mat4 mvpMat = vpMatrix * modelMat;

		m_shader->BindUniform("mvpMat", mvpMat);
		m_shader->BindUniform("modelMat", modelMat);
		m_shader->BindUniform("lightDir", light);

		segment->Bind();
		segment->Draw();
		segment->Unbind();
	}
}

void Mesh::LoadFromFile(const char* filePath)
{
	Assimp::Importer mesh_importer;

	const aiScene* scene = mesh_importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

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
				Vertex vert;

				vert.position.x = meshPointer->mVertices[index].x;
				vert.position.y = meshPointer->mVertices[index].y;
				vert.position.z = meshPointer->mVertices[index].z;

				if (meshPointer->HasNormals()) {
					vert.normal.x = meshPointer->mNormals[index].x;
					vert.normal.y = meshPointer->mNormals[index].y;
					vert.normal.z = meshPointer->mNormals[index].z;
				}

				vert.uv.x = meshPointer->mTextureCoords[0][index].x;
				vert.uv.y = meshPointer->mTextureCoords[0][index].y;

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
