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
    
    testShader = new ShaderProgram("simple.frag", "simple.vert");

    testShader->Use();

    testShader->BindUniform("faceColour", glm::vec4(1,0,0,1));
    
    meshes.push_back(new MeshContainer());

    meshes[0]->InitialiseFromFile("spider.obj");

    // mesh test matrix
    m_meshTransform = {
          1,0,0,0,
          0,1,0,0,
          0,0,1,0,
          0,0,0,10 };

    glClearColor(0.25f, 0.25f, 0.25f, 1);

    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    glm::vec3 camPos{ -50, 50 ,50};

    Gizmos::create(10000, 10000, 0, 0);
    m_view = glm::lookAt(camPos, vec3(0), vec3(0, 1, 0));
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
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

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

    //bind shader
    testShader->Use();

    // bind transform
    glm::mat4 transform = glm::rotate(m_meshTransform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    m_view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 3, 0), glm::vec3(0, 1, 0));
    m_projection = glm::perspective(3.14159f / 2.f, 1.7778f, 0.3f, 50.0f);

    auto pvm = m_projection * m_view * transform;
    testShader->BindUniform("ProjectionViewModel", pvm);

    //Draw mesh
    meshes[0]->Draw();

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