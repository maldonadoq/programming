#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.1416

// OpenGL V2
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (float t = 0.0f; t <= 2.0f * PI; t += 0.5f)
    {
        float x = cos(t);
        float y = sin(t);

        glVertex2f(x, y);
    }

    glEnd();
}

// g++ 11-parametricas.cpp -o 11-parametricas.out -I/opt/homebrew/opt/glfw/include -L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL
int main(int argc, char const *argv[])
{
    // Inicializar GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Crear ventana
    GLFWwindow *window = glfwCreateWindow(700, 600, "Parametricas OpenGL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}