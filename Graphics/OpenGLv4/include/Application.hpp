#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

enum class ProjectionMode
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Application
{
private:
    GLFWwindow *window;

    int width;
    int height;

    Camera camera;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Scene> scene;

    ProjectionMode projectionMode;

    float lastFrame;

    void initializeWindow();
    void processInput(float deltaTime);
    void render();
    void updateTitle();

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void framebufferCallback(GLFWwindow *window, int width, int height);

public:
    Application(int width, int height);
    ~Application();

    void run();
};

#endif // __APPLICATION_HPP__