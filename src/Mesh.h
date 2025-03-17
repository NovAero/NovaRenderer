#pragma once
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};
	
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	virtual ~Mesh();

	void Initialise(unsigned int vCount, const Vertex* verts, unsigned int iCount, unsigned int* indices = nullptr);
	void InitialiseQuad();

	virtual void Draw();

protected:

	unsigned int triCount;
	unsigned int vao, vbo, ibo;
	size_t indexCount;
};