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

	static Application* Get() { return s_instance; }
	GLFWwindow* GetWindow() { return window; }

protected:

	std::vector<Mesh*> meshes;

	Camera* m_camera;
	ShaderProgram* testShader;

	GLFWwindow* window;
	std::string windowName = "NovaRenderer";

private:
	bool GLFWStartup(unsigned int windowWidth, unsigned int windowHeight);
	
	static Application* s_instance;
	
	unsigned int m_windowWidth = 1280;
	unsigned int m_windowHeight = 720;
};