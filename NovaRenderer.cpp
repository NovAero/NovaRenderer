
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

int main() {

    if (glfwInit() == false)
        return -1;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Nova Renderer", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return -2;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    // the rest of our code goes here!

    glClearColor(0.25f, 0.25f, 0.25f, 1);
    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    Gizmos::create(10000, 10000, 0, 0);
    mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

    while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Gizmos::clear();

        Gizmos::addTransform(glm::mat4(1));

        vec4 red(1,1,0,1);
        vec4 black(0, 0, 0, 1);

        for (int i = 0; i < 21; ++i) {
            Gizmos::addLine(vec3(-10 + i, 0, 10),
                vec3(-10 + i, 0, -10),
                i == 10 ? red : black);

            Gizmos::addLine(vec3(10, 0, -10 + i),
                vec3(-10, 0, -10 + i),
                i == 10 ? red : black);
        }

        Gizmos::draw(projection * view);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Gizmos::destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}