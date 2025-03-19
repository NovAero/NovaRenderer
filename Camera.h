#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Graphics.h"

class Camera {
public:

	void Update(float deltaTime, GLFWwindow* window);

	void SetPosition(glm::vec3 pos);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float w, float h);

private:
	float m_theta = 0.f;
	float m_phi = 0.f;
	glm::vec3 m_pos;

	float aspectRatio = 16.0f / 9.0f;
};