#pragma once

#include "Graphics.h"
#include "Vertex.h"
#include <vector>

class MeshSegment {
public:
	
	MeshSegment() = default;
	MeshSegment(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~MeshSegment();

	MeshSegment(const MeshSegment& other) = delete;
	MeshSegment& operator=(MeshSegment& other) = delete;

	void Bind();
	void Unbind();
	void Draw();

protected:

	void Initialise(unsigned int vCount, const Vertex* verts, unsigned int iCount, unsigned int* indices = nullptr);

	GLuint vertexBufferID = 0;
	int vertCount = 0;

};