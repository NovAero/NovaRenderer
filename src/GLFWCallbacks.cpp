#include "GLFWCallbacks.h"
#include "Camera.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) {
        return;
    }

    glViewport(0, 0, width, height);

    Camera* mainCamera = (Camera*)glfwGetWindowUserPointer(window);
    mainCamera->aspectRatio = width / (float)height;
}
