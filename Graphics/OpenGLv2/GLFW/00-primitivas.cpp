#include <GLFW/glfw3.h>

// OpenGL V2
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.5f, 0.8f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.2f, 0.7f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(0.8f, -0.5f);
    glEnd();

    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.5f, -0.8f);
    glVertex2f(0.0f, -0.8f);
    glVertex2f(0.5f, -0.8f);
    glEnd();
}

int main(int argc, char const *argv[])
{
    // Inicializar GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Crear ventana
    GLFWwindow *window = glfwCreateWindow(
        700, 600,
        "Primitivas OpenGL",
        nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Activar el contexto OpenGL
    glfwMakeContextCurrent(window);

    // Color de fondo: blanco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Bucle principal
    while (!glfwWindowShouldClose(window))
    {
        display();

        // Intercambiar buffers
        glfwSwapBuffers(window);

        // Procesar eventos
        glfwPollEvents();
    }

    // Liberar recursos
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}