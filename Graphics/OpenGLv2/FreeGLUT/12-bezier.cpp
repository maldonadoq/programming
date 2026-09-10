#include <GL/glut.h>
#include <cmath>

struct Punto
{
    float x;
    float y;
};

// Bézier cuadrática
Punto p0 = {-0.9f, -0.2f};
Punto p1 = {-0.5f, 0.8f};
Punto p2 = {-0.1f, -0.2f};

// Bézier cúbica
Punto q0 = {0.1f, -0.2f};
Punto q1 = {0.3f, 0.8f};
Punto q2 = {0.7f, -0.8f};
Punto q3 = {0.9f, 0.4f};

float dt = 0.025f;

Punto bezierCuadratica(float t, Punto a, Punto b, Punto c)
{
    Punto p;

    p.x = pow(1 - t, 2) * a.x +
          2 * (1 - t) * t * b.x +
          pow(t, 2) * c.x;

    p.y = pow(1 - t, 2) * a.y +
          2 * (1 - t) * t * b.y +
          pow(t, 2) * c.y;

    return p;
}

Punto bezierCubica(float t, Punto a, Punto b, Punto c, Punto d)
{
    Punto p;

    p.x = pow(1 - t, 3) * a.x +
          3 * pow(1 - t, 2) * t * b.x +
          3 * (1 - t) * pow(t, 2) * c.x +
          pow(t, 3) * d.x;

    p.y = pow(1 - t, 3) * a.y +
          3 * pow(1 - t, 2) * t * b.y +
          3 * (1 - t) * pow(t, 2) * c.y +
          pow(t, 3) * d.y;

    return p;
}

void dibujarPunto(Punto p)
{
    glPointSize(8.0f);

    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

void dibujarControlCuadratica()
{
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINE_STRIP);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);

    dibujarPunto(p0);
    dibujarPunto(p1);
    dibujarPunto(p2);
}

void dibujarControlCubica()
{
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINE_STRIP);
    glVertex2f(q0.x, q0.y);
    glVertex2f(q1.x, q1.y);
    glVertex2f(q2.x, q2.y);
    glVertex2f(q3.x, q3.y);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);

    dibujarPunto(q0);
    dibujarPunto(q1);
    dibujarPunto(q2);
    dibujarPunto(q3);
}

void dibujarBezierCuadratica()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);

    for (float t = 0.0f; t <= 1.0f; t += dt)
    {
        Punto p = bezierCuadratica(t, p0, p1, p2);
        glVertex2f(p.x, p.y);
    }

    glEnd();
}

void dibujarBezierCubica()
{
    glColor3f(0.0f, 0.7f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);

    for (float t = 0.0f; t <= 1.0f; t += dt)
    {
        Punto p = bezierCubica(t, q0, q1, q2, q3);
        glVertex2f(p.x, p.y);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    dibujarControlCuadratica();
    dibujarBezierCuadratica();

    dibujarControlCubica();
    dibujarBezierCubica();

    glFlush();
}

void inicializar()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(900, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Curvas de Bezier - Cuadratica y Cubica");

    inicializar();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}