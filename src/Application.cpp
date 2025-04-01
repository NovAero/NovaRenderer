#include "Application.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include <sstream>

Application* Application::s_instance = nullptr;

bool Application::Initialise(unsigned int windowWidth, unsigned int windowHeight)
{
    if (!GLFWStartup(windowWidth, windowHeight)) return false;

    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;

    //Asset loading
    testShader = new ShaderProgram("BasicLitMaterial.frag", "BasicLitMaterial.vert");


    Texture* tex = new Texture();
    tex->LoadFromFile("soulspear_diffuse.tga");

    Material* mat = new Material("soulspear.mtl");

    //Set up rendering state
    glEnable(GL_DEPTH_TEST); // enables the depth buffer
    glClearColor(0.1f, 0.25f, 0.25f, 1);

    //Scene stuff , callbacks, camera pos, etc
    m_camera = new Camera();
    glfwSetWindowUserPointer(window, m_camera);

    m_camera->position = glm::vec3(0,5,2);
    m_camera->pitch = glm::radians(-30.f);

    lights.push_back(new DirLight(glm::vec4(0, -1, 0, 0.0), glm::vec3(1, 1, 1),
                                glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));

    lights.push_back(new PointLight(glm::vec4(0, 3,0, 1), glm::vec3(0.1, 0.5, 0.5),
                                glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));

    /*lights.push_back(new PointLight(glm::vec4(0, 0, 1, 10), glm::vec3(0.5, 0.5, 0.5),
                                glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)));

    lights.push_back(new PointLight(glm::vec4(-1, 1, 0, 1), glm::vec3(0.5, 0.5, 0.5),
                                glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)));

    lights.push_back(new PointLight(glm::vec4(0, 1, 1, 10), glm::vec3(0.5, 0.5, 0.5),
                                glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)));*/

    //Initalise mesh
    for (int i = 0; i < 3; ++i) {

        meshes.push_back(new Mesh());
        meshes[i]->LoadFromFile("soulspear.obj");

        meshes[i]->m_shader = new ShaderProgram("BasicLitMaterial.frag", "BasicLitMaterial.vert");
        meshes[i]->m_texture = tex;
        meshes[i]->m_material = mat;
        meshes[i]->position = glm::vec3(i + 1,0,0);
        meshes[i]->scale = glm::vec3(1);
        meshes[i]->lights = lights;
    }

    Mesh* cube = new Mesh();
    cube->LoadFromFile("box.obj");
    cube->m_shader = testShader;
    cube->m_material = mat;
    cube->position = dynamic_cast<PointLight*>(lights[1])->GetPosition();
    cube->scale = glm::vec3(1);
    cube->lights = lights;

    meshes.push_back(cube);

    return true;
}


bool Application::Update()
{
    float time = glfwGetTime();
    delta = time - prevDelta;
    prevDelta = time;
    
    m_camera->Update(delta, window);

    m_lastMousePos = m_mousePos;

    return glfwWindowShouldClose(window) == false &&
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Application::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.25f, 0.25f, 0.25f, 1);

    glm::mat4 vpMat = m_camera->GetVPMatrix();

    //Draw mesh

    for (int i = 0; i < 3; ++i) {
        meshes[i]->rotation.y = sin(glfwGetTime());
        meshes[i]->m_shader->Use();
        meshes[i]->Draw(vpMat, m_camera->position);
    }

    meshes[3]->m_shader->Use();
    meshes[3]->Draw(vpMat, m_camera->position);

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

void Application::SetMousePosition(GLFWwindow* window, double x, double y)
{
    s_instance->m_mousePos.x = (float)x;
    s_instance->m_mousePos.y = (float)y;
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
    glfwSetCursorPosCallback(window, &Application::SetMousePosition);

    return true;
}

