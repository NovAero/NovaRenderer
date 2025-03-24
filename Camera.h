#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Graphics.h"

class Camera {
public:

	void Update(float delta, GLFWwindow* window);

	glm::mat4 GetVPMatrix() const;
	glm::vec3 GetForwardVec() const;
	glm::vec3 GetRightVec() const;

public:

	glm::vec3 position;
	float camSpeed = 2.f;

	float pitch = 0.0f; //looking up and down
	float yaw = 0.0f; //looking left and right
	//float roll = 0.0f; //skewing the camera, let's just not do this

	float aspectRatio = 16.0f / 9.0f;
	float nearClip = 0.1f;
	float farClip = 200.f;

	float fov = glm::radians(90.0f);
};