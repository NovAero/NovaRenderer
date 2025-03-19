#pragma once
#include <vector>

class Mesh;
class ShaderProgram;
class Texture;

class MeshContainer {
public:
	MeshContainer();
	~MeshContainer();

	void InitialiseFromFile(const char* filePath);
	
	void WrapTexture(const char* textPath);
	void Draw();

private:
	
	void AddMesh(Mesh* mesh);

private:

	ShaderProgram* m_shader;
	Texture* m_texture;
	std::vector<Mesh*> m_children;

};