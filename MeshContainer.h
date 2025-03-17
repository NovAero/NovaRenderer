#pragma once

#include <vector>

class Mesh;

class MeshContainer {
public:
	MeshContainer();
	~MeshContainer();

	void InitialiseFromFile(const char* filePath);
	void Draw();

private:
	
	void AddMesh(Mesh* mesh);

private:

	std::vector<Mesh*> m_children;

};