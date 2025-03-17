#include "Mesh.h"
#include "glad.h"

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	Initialise(vertices.size(), vertices.data(), indices.size(), indices.data());
}

void Mesh::Initialise(unsigned int vCount, const Vertex* verts, unsigned int iCount, unsigned int* indices)
{
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(Vertex), verts, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// bind indices if there are any
	if (iCount != 0) {
		glGenBuffers(1, &ibo);

		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = iCount / 3;
	}
	else {
		triCount = vCount / 3;
	}

	indexCount = iCount;

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::InitialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f};
	vertices[1].position = { 0.5f, 0, 0.5f};
	vertices[2].position = { -0.5f, 0, -0.5f};

	vertices[3].position = { -0.5f, 0, -0.5f};
	vertices[4].position = { 0.5f, 0, 0.5f };
	vertices[5].position = { 0.5f, 0, -0.5f};

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles
	triCount = 2;
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	//using indices or just vertexes?
	if (ibo != 0) {
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
