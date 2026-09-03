#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>

// CONFIGURACION
namespace Config
{
    float PI = 3.14159265f;

    int ANCHO = 900;
    int ALTO = 650;

    float FOV = 60.0f;
    float NEAR_PLANE = 1.0f;
    float FAR_PLANE = 20.0f;

    float VELOCIDAD = 0.5f;
    float PASO_ROTACION = 5.0f;
}

// VECTOR 3D
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

    static Vector3 cruz(const Vector3 &a, const Vector3 &b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
    }
};

// CAMARA
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

        Vector3 direccion = {
            static_cast<float>(std::cos(yawRad) * std::cos(pitchRad)),
            static_cast<float>(std::sin(pitchRad)),
            static_cast<float>(std::sin(yawRad) * std::cos(pitchRad))};

        return direccion.normalizado();
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

    void mover(unsigned char tecla)
    {
        Vector3 adelante = direccion();
        Vector3 lateral = derecha();

        switch (tecla)
        {
        case 'w':
            posicion = posicion + adelante * Config::VELOCIDAD;
            break;

        case 's':
            posicion = posicion - adelante * Config::VELOCIDAD;
            break;

        case 'a':
            posicion = posicion - lateral * Config::VELOCIDAD;
            break;

        case 'd':
            posicion = posicion + lateral * Config::VELOCIDAD;
            break;

        case 'q':
            posicion.y -= Config::VELOCIDAD;
            break;

        case 'e':
            posicion.y += Config::VELOCIDAD;
            break;

        case 'j':
            yaw -= Config::PASO_ROTACION;
            break;

        case 'l':
            yaw += Config::PASO_ROTACION;
            break;

        case 'i':
            pitch += Config::PASO_ROTACION;
            if (pitch > 85)
                pitch = 85;
            break;

        case 'k':
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

// ESCENA
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
        glutWireCube(2);
        glPopMatrix();
    }

    void dibujarEsfera()
    {
        glColor3f(0.2f, 1.0f, 0.3f);

        glPushMatrix();
        glTranslatef(3, 1, -4);
        glutWireSphere(1.3, 18, 18);
        glPopMatrix();
    }

    void dibujarCono()
    {
        glColor3f(0.2f, 0.5f, 1.0f);

        glPushMatrix();
        glTranslatef(0, 0, -8);
        glRotatef(-90, 1, 0, 0);
        glutWireCone(1.4, 3, 18, 10);
        glPopMatrix();
    }

    void dibujarToroide()
    {
        glColor3f(1.0f, 1.0f, 0.2f);

        glPushMatrix();
        glTranslatef(-4, 1.5f, -12);
        glutWireTorus(0.3, 1.2, 15, 25);
        glPopMatrix();
    }

    void dibujarTetera()
    {
        glColor3f(1.0f, 0.3f, 1.0f);

        glPushMatrix();
        glTranslatef(4, 1.5f, -15);
        glutWireTeapot(1.5);
        glPopMatrix();
    }

public:
    void dibujarMalla()
    {
        glColor3f(0.25f, 0.25f, 0.25f);

        glBegin(GL_LINES);

        for (int i = -20; i <= 20; i++)
        {
            // Paralelas a Z
            glVertex3f(i, 0, -20);
            glVertex3f(i, 0, 20);

            // Paralelas a X
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
        dibujarTetera();
    }

    void dibujar()
    {
        dibujarMalla();
        dibujarObjetos();
    }
};

// TIPO DE VISTA
enum class TipoVista
{
    ORTOGRAFICA_2D,
    PERSPECTIVA_3D
};

// APLICACION
class Aplicacion
{
private:
    Camara camara;
    Escena escena;

    TipoVista vista = TipoVista::ORTOGRAFICA_2D;

    int ancho = Config::ANCHO;
    int alto = Config::ALTO;

    bool es3D() const
    {
        return vista == TipoVista::PERSPECTIVA_3D;
    }

    std::string numero(float valor)
    {
        std::ostringstream ss;

        ss.precision(1);
        ss << std::fixed << valor;

        return ss.str();
    }

    void escribirTexto(
        float x,
        float y,
        const std::string &texto)
    {
        glRasterPos2f(x, y);

        for (char caracter : texto)
        {
            glutBitmapCharacter(
                GLUT_BITMAP_8_BY_13,
                caracter);
        }
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
                static_cast<float>(ancho) / alto,
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
            // Vista superior del plano XZ
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

    void dibujarInterfaz2D()
    {
        escribirTexto(20, alto - 30, "VISTA 2D - PROYECCION ORTOGRAFICA");
        escribirTexto(20, alto - 50, "Vista superior del plano XZ");
        escribirTexto(20, alto - 80, "[2] Cambiar a vista 3D");
    }

    void dibujarInterfaz3D()
    {
        escribirTexto(20, alto - 30, "VISTA 3D - PROYECCION PERSPECTIVA");

        std::string limites =
            "Near: " + numero(Config::NEAR_PLANE) +
            "   Far: " + numero(Config::FAR_PLANE);

        escribirTexto(20, alto - 55, limites);
        escribirTexto(20, alto - 75, "Solo se renderizan objetos entre Near y Far");
        escribirTexto(20, alto - 105, "W/S: avanzar-retroceder | A/D: izquierda-derecha");
        escribirTexto(20, alto - 125, "Q/E: bajar-subir | J/L: girar");
        escribirTexto(20, alto - 145, "I/K: mirar arriba-abajo");
        escribirTexto(20, alto - 165, "R: reiniciar | [1]: vista 2D");
    }

    void dibujarInterfaz()
    {
        glDisable(GL_DEPTH_TEST);

        // Guardar proyección 3D
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        // Proyección temporal para texto
        gluOrtho2D(0, ancho, 0, alto);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(1, 1, 1);

        if (es3D())
            dibujarInterfaz3D();
        else
            dibujarInterfaz2D();

        escribirTexto(20, 20, "ESC: salir");

        // Recuperar matrices
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_DEPTH_TEST);
    }

public:
    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        configurarProyeccion();
        configurarVista();

        escena.dibujar();
        dibujarInterfaz();

        glutSwapBuffers();
    }

    void teclado(unsigned char tecla)
    {
        switch (tecla)
        {
        case '1':
            vista = TipoVista::ORTOGRAFICA_2D;
            break;

        case '2':
            vista = TipoVista::PERSPECTIVA_3D;
            break;

        case 'r':
            if (es3D())
                camara.reiniciar();
            break;

        case 27:
            std::exit(0);
            break;

        default:
            if (es3D())
                camara.mover(tecla);
        }

        glutPostRedisplay();
    }

    void reshape(int w, int h)
    {
        ancho = w;
        alto = (h > 0) ? h : 1;
        glViewport(0, 0, ancho, alto);
    }
};

// CALLBACKS GLUT
Aplicacion app;

void display()
{
    app.display();
}

void teclado(
    unsigned char tecla,
    int,
    int)
{
    app.teclado(tecla);
}

void reshape(int ancho, int alto)
{
    app.reshape(ancho, alto);
}

// MAIN
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(Config::ANCHO, Config::ALTO);
    glutCreateWindow("Camara 2D -> 3D");
    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}