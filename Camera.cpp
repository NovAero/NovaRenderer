#pragma once
#include "Camera.h"
#include "Application.h"

void Camera::Update(float deltaTime, GLFWwindow* window)
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);

    //calculate the forwards and right axes and up axis for the camera
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
    glm::vec3 up(0, 1, 0);

    // use WASD, ZX keys to move camera around
    if (glfwGetKey(window, GLFW_KEY_X)) {
        m_pos += up * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_Z)) {
        m_pos -= up * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_W)) {
        m_pos += forward * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        m_pos -= forward * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        m_pos += right * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        m_pos -= right * deltaTime;
    } 
    if (glfwGetKey(window, GLFW_KEY_R)) {
        SetPosition(glm::vec3(0, 10, 0));
    }

    glm::vec2 mouseDelta = Application::Get()->GetMouseDelta();

    const float turnSpeed = 0.1f;
    // if the right button is down, increment theta and phi
    if (glfwGetMouseButton(window, 1))
    {
        m_theta += turnSpeed * mouseDelta.x;
        m_phi -= turnSpeed * mouseDelta.y;
    }
}

void Camera::SetPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::mat4 Camera::GetViewMatrix()
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    return glm::lookAt(m_pos, m_pos + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float w, float h)
{
    return glm::perspective(glm::pi<float>() * 0.25f,
        w / h,
        0.1f, 1000.f);
}