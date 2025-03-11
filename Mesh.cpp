#include "Mesh.h"

#include "glad.h"

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::InitialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);
}
