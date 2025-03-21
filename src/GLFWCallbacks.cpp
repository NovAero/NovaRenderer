#include "GLFWCallbacks.h"
#include "Camera.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Camera* mainCamera = (Camera*)glfwGetWindowUserPointer(window);
    mainCamera->aspectRatio = width / (float)height;
}
