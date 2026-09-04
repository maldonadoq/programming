#include "Application.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Config
{
    const float FOV = 60.0f;
    const float NEAR_PLANE = 1.0f;
    const float FAR_PLANE = 20.0f;
}

Application::Application(int width, int height)
    : window(nullptr),
      width(width),
      height(height),
      projectionMode(ProjectionMode::PERSPECTIVE),
      lastFrame(0.0f)
{
    initializeWindow();

    shader = std::make_unique<Shader>("shaders/basic.vert", "shaders/basic.frag");
    scene = std::make_unique<Scene>();

    updateTitle();
}

Application::~Application()
{
    scene.reset();
    shader.reset();

    if (window)
        glfwDestroyWindow(window);

    glfwTerminate();
}

void Application::initializeWindow()
{
    if (!glfwInit())
        throw std::runtime_error("No se pudo iniciar GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "Camara 2D - 3D", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("No se pudo crear la ventana");
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress));

    if (version == 0)
        throw std::runtime_error("No se pudo iniciar GLAD");

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferCallback);

    glfwSwapInterval(1);

    int framebufferWidth;
    int framebufferHeight;

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    width = framebufferWidth;
    height = framebufferHeight;

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
    std::cout << "GPU: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Framebuffer: " << width << " x " << height << '\n';
}

void Application::run()
{
    lastFrame = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::processInput(float deltaTime)
{
    if (projectionMode != ProjectionMode::PERSPECTIVE)
        return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.moveDown(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.moveUp(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        camera.turnLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        camera.turnRight(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        camera.lookUp(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera.lookDown(deltaTime);
}

glm::mat4 Application::getProjectionMatrix() const
{
    float aspect = static_cast<float>(width) / static_cast<float>(height);

    if (projectionMode == ProjectionMode::PERSPECTIVE)
    {
        return glm::perspective(glm::radians(Config::FOV), aspect, Config::NEAR_PLANE, Config::FAR_PLANE);
    }

    return glm::ortho(-12.0f, 12.0f, -10.0f, 10.0f, 0.1f, 100.0f);
}

glm::mat4 Application::getViewMatrix() const
{
    if (projectionMode == ProjectionMode::PERSPECTIVE)
    {
        return camera.getViewMatrix();
    }

    return glm::lookAt(
        glm::vec3(0.0f, 20.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f));
}

void Application::render()
{
    glClearColor(0.02f, 0.02f, 0.04f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();

    shader->setMat4("projection", getProjectionMatrix());
    shader->setMat4("view", getViewMatrix());

    scene->draw(*shader);
}

void Application::updateTitle()
{
    std::ostringstream title;

    if (projectionMode == ProjectionMode::PERSPECTIVE)
    {
        title << "VISTA 3D - PERSPECTIVA | Near: " << Config::NEAR_PLANE << " | Far: " << Config::FAR_PLANE << " | [1] 2D";
    }
    else
    {
        title << "VISTA 2D - ORTOGRAFICA | [2] 3D";
    }

    glfwSetWindowTitle(window, title.str().c_str());
}

void Application::keyCallback(GLFWwindow *window, int key, int, int action, int)
{
    if (action != GLFW_PRESS)
        return;

    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (!app)
        return;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    case GLFW_KEY_1:
        app->projectionMode = ProjectionMode::ORTHOGRAPHIC;
        app->updateTitle();
        break;

    case GLFW_KEY_2:
        app->projectionMode = ProjectionMode::PERSPECTIVE;
        app->updateTitle();
        break;

    case GLFW_KEY_R:
        app->camera.reset();
        break;
    }
}

void Application::framebufferCallback(GLFWwindow *window, int width, int height)
{
    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (!app)
        return;

    app->width = width;
    app->height = height > 0 ? height : 1;

    glViewport(0, 0, app->width, app->height);
}