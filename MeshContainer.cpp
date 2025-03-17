#include "MeshContainer.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

MeshContainer::MeshContainer()
{

}

MeshContainer::~MeshContainer()
{

}

void MeshContainer::InitialiseFromFile(const char* filePath)
{
	Assimp::Importer mesh_importer;

	const aiScene* scene = mesh_importer.ReadFile(filePath, aiProcess_Triangulate);

	if (!scene) return;

	//read over each mesh and add them to the scene
	for (unsigned int mesh_index = 0; mesh_index < scene->mNumMeshes; ++mesh_index) {

		//initialise std::vectors
		std::vector<unsigned int> indices;
		std::vector<Mesh::Vertex> vertices;

		//new mesh from scene 
		auto mesh = scene->mMeshes[mesh_index];

		//vertices | position, normal, texture coord
		for (unsigned int vx_ix = 0; vx_ix < mesh->mNumVertices; ++vx_ix) {

			//Read the vertex data and add to vertex buffer
			Mesh::Vertex vert{};

			vert.position.x = mesh->mVertices[vx_ix].x;
			vert.position.y = mesh->mVertices[vx_ix].y;
			vert.position.z = mesh->mVertices[vx_ix].z;

			if (mesh->mNormals) { //if there are normals included in the mesh
				vert.normal.x = mesh->mNormals[vx_ix].x;
				vert.normal.y = mesh->mNormals[vx_ix].y;
				vert.normal.z = mesh->mNormals[vx_ix].z;
			}

			//vert.texCoord.x = mesh->mTextureCoords[0][vx_ix].x;
			//vert.texCoord.y = mesh->mTextureCoords[0][vx_ix].y;
			
			vertices.push_back(vert);
		}

		for (unsigned int f_ix = 0; f_ix < mesh->mNumFaces; ++f_ix) {
			//get new face
			const auto& face = mesh->mFaces[f_ix];

			//get all the face's index data and add it to the index buffer
			for (unsigned int ix_ix = 0; ix_ix < face.mNumIndices; ++ix_ix) {
				indices.push_back(face.mIndices[ix_ix]);
			}
		}
		
		AddMesh(new Mesh(vertices, indices));
	}
}

void MeshContainer::Draw()
{
	for (auto child : m_children) {
		child->Draw();
	}
}

void MeshContainer::AddMesh(Mesh* mesh)
{
	m_children.push_back(mesh);
}
