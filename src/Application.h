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

	static Application* Get() { return s_instance; }
	
protected:

	std::vector<Mesh*> meshes;

	Camera* m_camera;
	ShaderProgram* testShader;

	GLFWwindow* window;
	std::string windowName = "NovaRenderer";

	static Application* s_instance;

private:

	bool GLFWStartup();

};