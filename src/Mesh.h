#pragma once
#include <vector>
#include "Graphics.h"
#include "Light.h"


class MeshSegment;
class ShaderProgram;
struct Texture;
struct Material;

class Mesh {
public:
	Mesh() = default;
	Mesh(const Mesh& other) = delete;
	~Mesh();

	Mesh& operator=(const Mesh& other) = delete;

	void Draw(glm::mat4 vpMatrix, glm::vec3 cameraPos) const;
	void LoadFromFile(const char* filePath);

private:
	void AddSegment(MeshSegment* mesh);

public:
	std::vector<MeshSegment*> m_segments;
	
	glm::vec3 position{ 0 };
	glm::vec3 rotation{ 0 };
	glm::vec3 scale{ 1 };

	Material* m_material = nullptr;
	ShaderProgram* m_shader = nullptr;
	std::vector<Light*> lights;
};