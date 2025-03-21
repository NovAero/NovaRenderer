#include "Application.h"
#include "Camera.h"
#include "Material.h"

Application* Application::s_instance = nullptr;

bool Application::Initialise(unsigned int windowWidth, unsigned int windowHeight)
{
    if (!GLFWStartup(windowWidth, windowHeight)) return false;




    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;

    //Asset loading
    testShader = new ShaderProgram("simple.frag", "simple.vert");

    meshes.push_back(new Mesh());
    meshes[0]->LoadFromFile("spider.obj");
    
    Texture* tex = new Texture();
    tex->LoadFromFile("SpiderTex.jpg");

    //Set up rendering state
    glEnable(GL_DEPTH_TEST); // enables the depth buffer
    glClearColor(0.1f, 0.25f, 0.25f, 1);
    testShader->Use();

    //Scene stuff , callbacks, camera pos, etc
    m_camera = new Camera();
    glfwSetWindowUserPointer(window, m_camera);

    m_camera->position = glm::vec3(-10, 10, 0);
    m_camera->pitch = glm::radians(-30.f);

    //initalise mesh
    meshes[0]->m_shader = testShader;
    meshes[0]->m_texture = tex;
    meshes[0]->position = glm::vec3(0,5,0);
    meshes[0]->scale = glm::vec3(0.1);

    return true;
}


bool Application::Update()
{
    m_camera->Update(0.1f, window);

    return glfwWindowShouldClose(window) == false &&
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Application::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.25f, 0.25f, 0.25f, 1);

    glm::mat4 vpMat = m_camera->GetVPMatrix();

    testShader->Use();
    //Draw mesh
    meshes[0]->Draw(vpMat);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Exit()
{
    Gizmos::destroy();

    delete testShader;
    delete m_camera;

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Application::GLFWStartup(unsigned int windowWidth, unsigned int windowHeight)
{
    if (glfwInit() == false)
        return false;
    window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
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

    return true;
}

