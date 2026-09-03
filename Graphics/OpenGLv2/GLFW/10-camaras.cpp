#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include "src/primitives.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// =====================================================
// CONFIGURACION
// =====================================================

namespace Config
{
    const float PI = 3.14159265f;

    const int ANCHO = 900;
    const int ALTO = 650;

    const float FOV = 60.0f;
    const float NEAR_PLANE = 1.0f;
    const float FAR_PLANE = 20.0f;

    const float VELOCIDAD = 0.5f;
    const float PASO_ROTACION = 5.0f;
}

// =====================================================
// VECTOR 3D
// =====================================================

struct Vector3
{
    float x, y, z;

    Vector3 operator+(const Vector3 &v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3 &v) const
    {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator*(float k) const
    {
        return {x * k, y * k, z * k};
    }

    float magnitud() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalizado() const
    {
        float m = magnitud();

        if (m == 0)
            return {0, 0, 0};

        return {x / m, y / m, z / m};
    }

    static Vector3 cruz(
        const Vector3 &a,
        const Vector3 &b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
    }
};

// =====================================================
// CAMARA
// =====================================================

class Camara
{
private:
    Vector3 posicion;
    float yaw;
    float pitch;

public:
    Camara()
        : posicion{0, 2, 10},
          yaw(-90),
          pitch(0)
    {
    }

    Vector3 direccion() const
    {
        float yawRad = yaw * Config::PI / 180.0f;
        float pitchRad = pitch * Config::PI / 180.0f;

        Vector3 dir = {
            static_cast<float>(
                std::cos(yawRad) *
                std::cos(pitchRad)),

            static_cast<float>(
                std::sin(pitchRad)),

            static_cast<float>(
                std::sin(yawRad) *
                std::cos(pitchRad))};

        return dir.normalizado();
    }

    Vector3 derecha() const
    {
        Vector3 arriba = {0, 1, 0};

        return Vector3::cruz(
                   direccion(),
                   arriba)
            .normalizado();
    }

    void aplicarVista() const
    {
        Vector3 d = direccion();

        gluLookAt(
            posicion.x,
            posicion.y,
            posicion.z,

            posicion.x + d.x,
            posicion.y + d.y,
            posicion.z + d.z,

            0, 1, 0);
    }

    void mover(int tecla)
    {
        Vector3 adelante = direccion();
        Vector3 lateral = derecha();

        switch (tecla)
        {
        case GLFW_KEY_W:
            posicion =
                posicion +
                adelante * Config::VELOCIDAD;
            break;

        case GLFW_KEY_S:
            posicion =
                posicion -
                adelante * Config::VELOCIDAD;
            break;

        case GLFW_KEY_A:
            posicion =
                posicion -
                lateral * Config::VELOCIDAD;
            break;

        case GLFW_KEY_D:
            posicion =
                posicion +
                lateral * Config::VELOCIDAD;
            break;

        case GLFW_KEY_Q:
            posicion.y -= Config::VELOCIDAD;
            break;

        case GLFW_KEY_E:
            posicion.y += Config::VELOCIDAD;
            break;

        case GLFW_KEY_J:
            yaw -= Config::PASO_ROTACION;
            break;

        case GLFW_KEY_L:
            yaw += Config::PASO_ROTACION;
            break;

        case GLFW_KEY_I:
            pitch += Config::PASO_ROTACION;

            if (pitch > 85)
                pitch = 85;
            break;

        case GLFW_KEY_K:
            pitch -= Config::PASO_ROTACION;

            if (pitch < -85)
                pitch = -85;
            break;
        }
    }

    void reiniciar()
    {
        posicion = {0, 2, 10};
        yaw = -90;
        pitch = 0;
    }
};

// =====================================================
// ESCENA
// =====================================================

class Escena
{
private:
    void dibujarEjes()
    {
        glLineWidth(2);
        glBegin(GL_LINES);

        // X
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(6, 0, 0);

        // Y
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 6, 0);

        // Z
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 6);

        glEnd();
        glLineWidth(1);
    }

    void dibujarCubo()
    {
        glColor3f(1.0f, 0.3f, 0.3f);
        glPushMatrix();

        glTranslatef(-3, 1, 0);
        Primitivas::cubo(2);

        glPopMatrix();
    }

    void dibujarEsfera()
    {
        glColor3f(0.2f, 1.0f, 0.3f);
        glPushMatrix();

        glTranslatef(3, 1, -4);
        Primitivas::esfera(1.3f, 18, 12);

        glPopMatrix();
    }

    void dibujarCono()
    {
        glColor3f(0.2f, 0.5f, 1.0f);
        glPushMatrix();

        glTranslatef(0, 0, -8);
        Primitivas::cono(1.4f, 3.0f, 18);

        glPopMatrix();
    }

    void dibujarToroide()
    {
        glColor3f(1.0f, 1.0f, 0.2f);
        glPushMatrix();

        glTranslatef(-4, 1.5f, -12);
        Primitivas::torus(0.3f, 1.2f, 12, 24);

        glPopMatrix();
    }

    void dibujarPiramide()
    {
        glColor3f(1.0f, 0.3f, 1.0f);
        glPushMatrix();

        glTranslatef(4, 1.5f, -15);
        Primitivas::cono(1.5f, 3.0f, 4);

        glPopMatrix();
    }

public:
    void dibujarMalla()
    {
        glColor3f(0.25f, 0.25f, 0.25f);
        glBegin(GL_LINES);

        for (int i = -20; i <= 20; i++)
        {
            glVertex3f(i, 0, -20);
            glVertex3f(i, 0, 20);
            glVertex3f(-20, 0, i);
            glVertex3f(20, 0, i);
        }

        glEnd();
        dibujarEjes();
    }

    void dibujarObjetos()
    {
        dibujarCubo();
        dibujarEsfera();
        dibujarCono();
        dibujarToroide();
        dibujarPiramide();
    }

    void dibujar()
    {
        dibujarMalla();
        dibujarObjetos();
    }
};

// =====================================================
// TIPO DE VISTA
// =====================================================

enum class TipoVista
{
    ORTOGRAFICA_2D,
    PERSPECTIVA_3D
};

// =====================================================
// APLICACION
// =====================================================

class Aplicacion
{
private:
    GLFWwindow *ventana;

    Camara camara;
    Escena escena;

    TipoVista vista =
        TipoVista::ORTOGRAFICA_2D;

    int ancho = Config::ANCHO;
    int alto = Config::ALTO;

    bool es3D() const
    {
        return vista ==
               TipoVista::PERSPECTIVA_3D;
    }

    void configurarProyeccion()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (!es3D())
        {
            glOrtho(
                -12, 12,
                -10, 10,
                -30, 30);
        }
        else
        {
            gluPerspective(
                Config::FOV,
                static_cast<float>(ancho) /
                    static_cast<float>(alto),
                Config::NEAR_PLANE,
                Config::FAR_PLANE);
        }

        glMatrixMode(GL_MODELVIEW);
    }

    void configurarVista()
    {
        glLoadIdentity();

        if (!es3D())
        {
            gluLookAt(
                0, 20, 0,
                0, 0, -5,
                0, 0, -1);
        }
        else
        {
            camara.aplicarVista();
        }
    }

    void actualizarTitulo()
    {
        std::ostringstream titulo;

        if (!es3D())
        {
            titulo
                << "Vista 2D - Ortografica"
                << " | [2] Cambiar a 3D";
        }
        else
        {
            titulo
                << "Vista 3D - Perspectiva"
                << " | Near: "
                << Config::NEAR_PLANE
                << " Far: "
                << Config::FAR_PLANE
                << " | [1] Vista 2D";
        }

        glfwSetWindowTitle(
            ventana,
            titulo.str().c_str());
    }

public:
    Aplicacion(GLFWwindow *window)
        : ventana(window)
    {
    }

    void renderizar()
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

        configurarProyeccion();
        configurarVista();

        escena.dibujar();

        glfwSwapBuffers(ventana);
    }

    void procesarTecla(
        int tecla,
        int accion)
    {
        if (accion != GLFW_PRESS &&
            accion != GLFW_REPEAT)
            return;

        switch (tecla)
        {
        case GLFW_KEY_1:

            vista =
                TipoVista::ORTOGRAFICA_2D;

            break;

        case GLFW_KEY_2:

            vista =
                TipoVista::PERSPECTIVA_3D;

            break;

        case GLFW_KEY_R:

            if (es3D())
                camara.reiniciar();

            break;

        case GLFW_KEY_ESCAPE:

            glfwSetWindowShouldClose(
                ventana,
                GLFW_TRUE);

            break;

        default:

            if (es3D())
                camara.mover(tecla);
        }

        actualizarTitulo();
    }

    void redimensionar(
        int nuevoAncho,
        int nuevoAlto)
    {
        ancho = nuevoAncho;

        alto =
            nuevoAlto > 0
                ? nuevoAlto
                : 1;

        glViewport(
            0,
            0,
            ancho,
            alto);
    }

    void mostrarControles()
    {
        std::cout
            << "\n===== CONTROLES =====\n"
            << "1 : Vista 2D\n"
            << "2 : Vista 3D\n"
            << "W/S : Avanzar / Retroceder\n"
            << "A/D : Izquierda / Derecha\n"
            << "Q/E : Bajar / Subir\n"
            << "J/L : Girar izquierda / derecha\n"
            << "I/K : Mirar arriba / abajo\n"
            << "R : Reiniciar camara\n"
            << "ESC : Salir\n"
            << "=====================\n\n";
    }
};

// =====================================================
// CALLBACKS GLFW
// =====================================================

Aplicacion *app = nullptr;

void tecladoCallback(
    GLFWwindow *,
    int tecla,
    int,
    int accion,
    int)
{
    if (app != nullptr)
        app->procesarTecla(
            tecla,
            accion);
}

void resizeCallback(
    GLFWwindow *,
    int ancho,
    int alto)
{
    if (app != nullptr)
        app->redimensionar(
            ancho,
            alto);
}

// =====================================================
// MAIN
// =====================================================

int main()
{
    if (!glfwInit())
    {
        std::cerr
            << "Error al iniciar GLFW\n";

        return -1;
    }

    GLFWwindow *ventana =
        glfwCreateWindow(
            Config::ANCHO,
            Config::ALTO,
            "Camara 2D -> 3D",
            nullptr,
            nullptr);

    if (!ventana)
    {
        std::cerr
            << "No se pudo crear la ventana\n";

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(ventana);

    glClearColor(
        0,
        0,
        0,
        1);

    glEnable(GL_DEPTH_TEST);

    Aplicacion aplicacion(ventana);
    app = &aplicacion;

    glfwSetKeyCallback(
        ventana,
        tecladoCallback);

    glfwSetFramebufferSizeCallback(
        ventana,
        resizeCallback);

    aplicacion.mostrarControles();

    while (!glfwWindowShouldClose(ventana))
    {
        aplicacion.renderizar();

        glfwPollEvents();
    }

    glfwDestroyWindow(ventana);
    glfwTerminate();

    return 0;
}