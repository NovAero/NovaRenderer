#include "Application.h"

bool Application::Initialise()
{
    if (glfwInit() == false)
        return false;

    window = glfwCreateWindow(windowWidth, windowHeight, "Nova Renderer", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    // the rest of our code goes here!

    glClearColor(0.25f, 0.25f, 0.25f, 1);
    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    Gizmos::create(10000, 10000, 0, 0);
    m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

    return true;
}

bool Application::Update()
{
    if (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        return true;
    }
    else {
        return false;
    }
}

void Application::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Gizmos::clear();

    Gizmos::addTransform(glm::mat4(1));

    vec4 yellow(1, 1, 0, 1);
    vec4 black(0, 0, 0, 1);

    for (int i = 0; i < 21; ++i) {
        Gizmos::addLine(vec3(-10 + i, 0, 10),
            vec3(-10 + i, 0, -10),
            i == 10 ? yellow : black);

        Gizmos::addLine(vec3(10, 0, -10 + i),
            vec3(-10, 0, -10 + i),
            i == 10 ? yellow : black);
    }

    Gizmos::draw(m_projection * m_view);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Exit()
{
    Gizmos::destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
}