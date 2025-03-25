#include "Application.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"

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
    testShader->Use();

    //Scene stuff , callbacks, camera pos, etc
    m_camera = new Camera();
    glfwSetWindowUserPointer(window, m_camera);

    m_camera->position = glm::vec3(0,2,2);
    m_camera->pitch = glm::radians(-30.f);

    lights[0] = new Light(glm::vec3(1, 0, 0), 30.f, glm::vec4(1, 1, 1, 1));
    LoadLighting();
    BindLightsToShader(testShader);

    //Initalise mesh
    for (int i = 0; i < 3; ++i) {

        meshes.push_back(new Mesh());
        meshes[i]->LoadFromFile("soulspear.obj");

        meshes[i]->m_shader = testShader;
        meshes[i]->m_texture = tex;
        meshes[i]->m_material = mat;
        meshes[i]->position = glm::vec3(i,0,0);
        if (i == 0) {
            meshes[i]->rotation = glm::vec3(lights[0]->GetLightVec().x, 0, 0);
        }
        meshes[i]->scale = glm::vec3(i + 1);
        meshes[i]->lights = lights[0];
    }


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

    testShader->Use();
    //Draw mesh

    for (int i = 0; i < 3; ++i) {
        meshes[i]->Draw(vpMat, m_camera->position);
    }

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

void Application::LoadLighting()
{
    unsigned int bufferSize = 4 * (sizeof(glm::vec3) + sizeof(glm::vec4));

    glGenBuffers(1, &lightUBO);
    //bind and allocate memory for 4 sets of vec3 and 4
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    //unbind
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Application::BindLightsToShader(ShaderProgram* shader)
{
    int lightSize = sizeof(glm::vec3) + sizeof(glm::vec4);
    unsigned int ubindex = glGetUniformBlockIndex(shader->ID(), "lights[0]");
    glUniformBlockBinding(shader->ID(), ubindex, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightUBO, 0, 4 * lightSize);

    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    
    for (int i = 0; i < 4; i++) {
        int offset = i * lightSize;

        if (lights[i] == nullptr) break;

        glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), glm::value_ptr(lights[i]->GetLightVec()));
        glBufferSubData(GL_UNIFORM_BUFFER, offset + sizeof(glm::vec3), sizeof(glm::vec4), glm::value_ptr(lights[i]->GetColour()));

    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

