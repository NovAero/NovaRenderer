#include "Application.h"
#include "ShaderProgram.h"

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

    glClearColor(0.25f, 0.25f, 0.25f, 1);

    //Uncomment for gizmos, depth buffer removes the ability to render a 2D shape
    //glEnable(GL_DEPTH_TEST); // enables the depth buffer

    //Gizmos::create(10000, 10000, 0, 0);
    //m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    //m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

    glGenBuffers(1, &vertexBufferID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * someFloats.size(), someFloats.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(0);

    testShader = new ShaderProgram("bin/Shaders/simple.frag", "bin/Shaders/simple.vert");

    testShader->Use();

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
    float rightNow = (float)glfwGetTime();
    float colourIntensity = sin(rightNow) * 0.5f + 0.5f;
    glClearColor(1.0f - colourIntensity, 0.0f, colourIntensity, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

   /* Gizmos::clear();

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

    Gizmos::draw(m_projection * m_view);*/

    testShader->SetFloatUniform("aspectRatio", 1.7778f);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, someFloats.size() / 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Exit()
{
    Gizmos::destroy();

    delete testShader;

    glfwDestroyWindow(window);
    glfwTerminate();
}