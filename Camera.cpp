#include "Camera.h"
#include "Application.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Camera::Update(float delta, GLFWwindow* window)
{
	//calculate the forwards and right axes and up axis for the camera
	glm::vec3 up(0, 1, 0);

	glm::vec2 mouseDelta = Application::Get()->GetMouseDelta();

	const float turnSpeed = 0.1f;
	// if the right button is down, increment theta and phi
	if (glfwGetMouseButton(window, 1))
	{
		yaw -= turnSpeed * mouseDelta.x * delta;
		pitch -= turnSpeed * mouseDelta.y * delta;
	}

	// use WASD, QE keys to move camera around
	if (glfwGetKey(window, GLFW_KEY_Q)) {
		position -= up * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_E)) {
		position += up * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += GetForwardVec() * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= GetForwardVec() * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += GetRightVec() * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position -= GetRightVec() * delta;
	}
}

glm::mat4 Camera::GetVPMatrix() const
{
	glm::mat4 projectionMat = glm::perspective(fov, aspectRatio, nearClip, farClip);

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

glm::vec3 Camera::GetRightVec() const
{
	glm::vec4 right(-1.f, 0.f, 0.f, 0.f);
	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, yaw, glm::vec3(0, 1, 0));
	rotationMat = glm::rotate(rotationMat, pitch, glm::vec3(1, 0, 0));

	right = rotationMat * right;

	return glm::vec3(right.x, right.y, right.z);
}
