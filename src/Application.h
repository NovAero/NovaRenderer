#pragma once

#include "Graphics.h"
#include "Gizmos.h"

#include "MeshContainer.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

class Camera;

const int windowWidth = 1280;
const int windowHeight = 720;

class Application {
public:

	virtual bool Initialise();
	virtual bool Update();
	virtual void Draw();
	virtual void Exit();

	static void SetMousePosition(GLFWwindow* window, double x, double y);

	const int GetWindowWidth() const { return windowWidth; }
	const int GetWindowHeight() const { return windowHeight; }

	static Application* Get() { return s_instance; }
	
	glm::vec2 GetMousePosition() { return m_mousePosition; }
	glm::vec2 GetMouseDelta() { return m_mousePosition - m_lastMousePosition; }

protected:

	std::vector<MeshContainer*> meshes;

	glm::mat4 m_meshTransform;

	Camera* m_camera;
	glm::vec2 m_mousePosition;
	glm::vec2 m_lastMousePosition;

	ShaderProgram* testShader;
	GLuint vertexBufferID = 0;

	GLFWwindow* window;

	static Application* s_instance;
	
	std::string windowName = "NovaRenderer";

private:

	bool GLFWStartup();

};