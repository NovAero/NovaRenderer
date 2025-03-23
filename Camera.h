#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Graphics.h"

class Camera {
public:

	void Update(float delta, GLFWwindow* window);

	glm::mat4 GetVPMatrix() const;
	glm::vec3 GetForwardVec() const;

public:

	glm::vec3 position;
	float camSpeed = 0.008f;
	float pitch = 0.0f; //looking up and down
	float yaw = 0.0f; //looking left and right
	//float roll = 0.0f; //skewing the camera, let's just not do this

	float aspectRatio = 16.0f / 9.0f;

	float fov = glm::radians(90.0f);
};