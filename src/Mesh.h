#pragma once
#include <vector>
#include "Graphics.h"

class MeshSegment;
class ShaderProgram;
class Texture;

class Mesh {
public:
	Mesh() = default;
	Mesh(const Mesh& other) = delete;
	~Mesh();

	Mesh& operator=(const Mesh& other) = delete;

	void Draw(glm::mat4 vpMatrix) const;

	void LoadFromFile(const char* filePath);

private:
	
	void AddSegment(MeshSegment* mesh);

public:
	glm::vec3 position{ 0 };
	glm::vec3 rotation{ 0 };
	glm::vec3 scale{ 1 };

	Texture* m_texture = nullptr;
	ShaderProgram* m_shader = nullptr;
	std::vector<MeshSegment*> m_segments;

};