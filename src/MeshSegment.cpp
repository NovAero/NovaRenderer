#include "MeshSegment.h"
#include "glad.h"


MeshSegment::MeshSegment(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	Initialise(vertices.size(), vertices.data(), indices.size(), indices.data());
}

MeshSegment::~MeshSegment()
{
	glDeleteBuffers(1, &vertexBufferID);
}

void MeshSegment::Initialise(unsigned int vCount, const Vertex* verts, unsigned int iCount, unsigned int* indices)
{
	// generate buffers
	glGenBuffers(1, &vertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vCount, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vertCount = vCount;
}

void MeshSegment::Bind()
{
	//enable vertex attributes for shader
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//bind buffer as current context
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, position)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, uv)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, normal)));

	//unbind as current context for application
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshSegment::Unbind()
{
	//disable vertex attribs
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void MeshSegment::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
