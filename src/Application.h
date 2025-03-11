#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>

#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

const int windowWidth = 1280;
const int windowHeight = 720;

class Application {
public:
	bool Initialise();
	bool Run();
	void Draw();
	void Exit();

protected:
	glm::mat4 view;
	glm::mat4 projection;

	GLFWwindow* window;
};