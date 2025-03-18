#include "Application.h"
#include "Camera.h"

Application* Application::s_instance = nullptr;

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

    s_instance = this;
    m_camera = new Camera();

    testShader = new ShaderProgram("simple.frag", "simple.vert");

    testShader->Use();

    testShader->BindUniform("faceColour", glm::vec4(1,0,0,1));
    

    meshes.push_back(new MeshContainer());

    meshes[0]->InitialiseFromFile("spider.obj");

    // mesh test matrix
    m_meshTransform = {
          0.1,0,0,0,
          0,0.1,0,0,
          0,0,0.1,0,
          0,0,0,1 };

    glClearColor(0.25f, 0.25f, 0.25f, 1);

    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    glm::vec3 camPos{ -50, 50 ,50};

    Gizmos::create(10000, 10000, 0, 0);

    glfwSetCursorPosCallback(window, &SetMousePosition);

  //  m_view = glm::lookAt(camPos, vec3(0), vec3(0, 1, 0));
   // m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

    return true;
}

bool Application::Update()
{
    m_camera->Update(0.1f, window);
    m_lastMousePosition = m_mousePosition;

    return glfwWindowShouldClose(window) == false &&
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Application::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

    Gizmos::clear();

    Gizmos::addTransform(glm::mat4(1));

    glm::mat4 pv = m_camera->GetProjectionMatrix(windowWidth, windowHeight) * m_camera->GetViewMatrix();

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

    Gizmos::draw(pv);

    //bind shader
    testShader->Use();

    //bind transform
    glm::mat4 transform = glm::rotate(m_meshTransform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::translate(transform, glm::vec3(0, 3, 0));

    auto pvm = pv * transform;
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

void Application::SetMousePosition(GLFWwindow* window, double x, double y)
{
    s_instance->m_mousePosition.x = (float)x;
    s_instance->m_mousePosition.y = (float)y;
}

