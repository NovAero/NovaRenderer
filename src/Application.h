#pragma once

#include "Graphics.h"
#include "Gizmos.h"

#include "Mesh.h"
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

class Application {
public:

	virtual bool Initialise(unsigned int windowWidth, unsigned int windowHeight);
	virtual bool Update();
	virtual void Draw();
	virtual void Exit();

	const int GetWindowWidth() const { return m_windowWidth; }
	const int GetWindowHeight() const { return m_windowHeight; }

	glm::vec2 GetMousePosition() const { return m_mousePos; }
	glm::vec2 GetMouseDelta() const	{ return m_mousePos - m_lastMousePos; }

	static void SetMousePosition(GLFWwindow* window, double x, double y);
	static Application* Get() { return s_instance; }
	GLFWwindow* GetWindow() { return window; }

public:

	float delta = 0.f;

protected:

	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;

	Camera* m_camera;

	glm::vec2 m_mousePos;
	glm::vec2 m_lastMousePos;

	GLFWwindow* window;
	std::string windowName = "NovaRenderer";

private:
	bool GLFWStartup(unsigned int windowWidth, unsigned int windowHeight);
	
	static Application* s_instance;
	
	float prevDelta = 0.f;

	unsigned int m_windowWidth = 1280;
	unsigned int m_windowHeight = 720;
};