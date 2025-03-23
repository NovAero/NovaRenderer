#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Camera::Update(float delta, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		yaw += camSpeed * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		yaw -= camSpeed * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pitch += camSpeed * delta;
		if (pitch > glm::radians(80.0f))
		{
			pitch = glm::radians(80.0f);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pitch -= camSpeed * delta;
		if (pitch < glm::radians(-80.0f))
		{
			pitch = glm::radians(-80.0f);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += GetForwardVec() * 0.01f;
	}
}

glm::mat4 Camera::GetVPMatrix() const
{
	glm::mat4 projectionMat = glm::perspective(fov, aspectRatio, 0.3f, 200.0f);

	glm::mat4 viewMat(1);
	viewMat = glm::translate(viewMat, position);

	viewMat = glm::rotate(viewMat, yaw, glm::vec3(0, 1, 0));
	viewMat = glm::rotate(viewMat, pitch, glm::vec3(1, 0, 0));

	viewMat = glm::inverse(viewMat);

	return projectionMat * viewMat;

}

glm::vec3 Camera::GetForwardVec() const
{
	glm::vec4 forward(0.0f, 0.0f, -1.0f, 0.0f);
	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, yaw, glm::vec3(0, 1, 0));
	rotationMat = glm::rotate(rotationMat, pitch, glm::vec3(1, 0, 0));

	forward = rotationMat * forward;

	return glm::vec3(forward.x, forward.y, forward.z);
}