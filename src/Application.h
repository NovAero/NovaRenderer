#pragma once

#include "Graphics.h"

#include "Gizmos.h"
#include "MeshContainer.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

const int windowWidth = 1280;
const int windowHeight = 720;

class Application {
public:
	virtual bool Initialise();
	virtual bool Update();
	virtual void Draw();
	virtual void Exit();

	const int GetWindowWidth() const { return windowWidth; }
	const int GetWindowHeight() const { return windowHeight; }

protected:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	std::vector<MeshContainer*> meshes;

	glm::mat4 m_meshTransform;

	ShaderProgram* testShader;
	GLuint vertexBufferID = 0;

	GLFWwindow* window;
};