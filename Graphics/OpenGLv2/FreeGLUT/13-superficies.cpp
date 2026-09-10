#include <GL/glut.h>
#include <cmath>

void dibujarPrismaExtrusion()
{

    float z1 = -0.5f;
    float z2 = 0.5f;

    glBegin(GL_QUADS);

    // Cara frontal
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(-1.0f, -1.0f, z1);
    glVertex3f(1.0f, -1.0f, z1);
    glVertex3f(1.0f, 1.0f, z1);
    glVertex3f(-1.0f, 1.0f, z1);

    // Cara posterior
    glColor3f(0.2f, 0.8f, 0.5f);
    glVertex3f(-1.0f, -1.0f, z2);
    glVertex3f(-1.0f, 1.0f, z2);
    glVertex3f(1.0f, 1.0f, z2);
    glVertex3f(1.0f, -1.0f, z2);

    // Lado izquierdo
    glVertex3f(-1.0f, -1.0f, z1);
    glVertex3f(-1.0f, 1.0f, z1);
    glVertex3f(-1.0f, 1.0f, z2);
    glVertex3f(-1.0f, -1.0f, z2);

    // Lado derecho
    glVertex3f(1.0f, -1.0f, z1);
    glVertex3f(1.0f, -1.0f, z2);
    glVertex3f(1.0f, 1.0f, z2);
    glVertex3f(1.0f, 1.0f, z1);

    // Superior
    glVertex3f(-1.0f, 1.0f, z1);
    glVertex3f(1.0f, 1.0f, z1);
    glVertex3f(1.0f, 1.0f, z2);
    glVertex3f(-1.0f, 1.0f, z2);

    // Inferior
    glVertex3f(-1.0f, -1.0f, z1);
    glVertex3f(-1.0f, -1.0f, z2);
    glVertex3f(1.0f, -1.0f, z2);
    glVertex3f(1.0f, -1.0f, z1);

    glEnd();
}

const float PI = 3.1415926f;

void dibujarRevolucion()
{

    const int segmentos = 40;

    float radios[] = {
        0.2f,
        0.4f,
        0.6f,
        0.8f,
        0.7f,
        0.5f};

    float alturas[] = {
        -1.5f,
        -1.0f,
        -0.5f,
        0.0f,
        0.5f,
        1.0f};

    const int puntosPerfil = 6;

    for (int i = 0; i < puntosPerfil - 1; i++)
    {

        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j <= segmentos; j++)
        {

            float angulo = 2.0f * PI * j / segmentos;

            float x1 = radios[i] * cos(angulo);
            float z1 = radios[i] * sin(angulo);

            float x2 = radios[i + 1] * cos(angulo);
            float z2 = radios[i + 1] * sin(angulo);

            glColor3f(0.7f, 0.4f, 0.9f);

            glVertex3f(x1, alturas[i], z1);
            glVertex3f(x2, alturas[i + 1], z2);
        }

        glEnd();
    }
}

void dibujarBarrido()
{

    const int segmentosTrayectoria = 50;
    const int segmentosPerfil = 20;

    float radioTubo = 0.2f;

    for (int i = 0; i < segmentosTrayectoria; i++)
    {

        float t1 = i * 0.1f;
        float t2 = (i + 1) * 0.1f;

        float cx1 = t1 - 2.5f;
        float cy1 = 0.5f * sin(t1);

        float cx2 = t2 - 2.5f;
        float cy2 = 0.5f * sin(t2);

        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j <= segmentosPerfil; j++)
        {

            float angulo = 2.0f * PI * j / segmentosPerfil;

            float y1 = cy1 + radioTubo * cos(angulo);
            float z1 = radioTubo * sin(angulo);

            float y2 = cy2 + radioTubo * cos(angulo);
            float z2 = radioTubo * sin(angulo);

            glColor3f(1.0f, 0.5f, 0.2f);

            glVertex3f(cx1, y1, z1);
            glVertex3f(cx2, y2, z2);
        }

        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        4.0, 3.0, 7.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    // Elegir uno:
    // dibujarPrismaExtrusion();
    dibujarRevolucion();
    // dibujarBarrido();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0)
    {
        h = 1;
    }

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        (float)w / (float)h,
        0.1,
        100.0);

    glMatrixMode(GL_MODELVIEW);
}

void inicializar()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH);

    glutInitWindowSize(900, 600);

    glutCreateWindow(
        "Modelado geometrico");

    inicializar();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}