#include <GL/glut.h>

float anguloBrazo = 0.0f;
float posicionX = 0.0f;
float escalaRobot = 1.0f;

void cubo(float x, float y, float z,
          float sx, float sy, float sz)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glutSolidCube(1.0);

    glPopMatrix();
}

void dibujarRobot()
{
    glPushMatrix();

    // Transformaciones globales del robot
    glTranslatef(posicionX, 0.0f, 0.0f);
    glScalef(escalaRobot, escalaRobot, escalaRobot);

    // Cuerpo
    glColor3f(0.2f, 0.5f, 0.9f);

    cubo(
        0.0f, 1.5f, 0.0f,
        1.5f, 2.0f, 0.8f);

    // Cabeza
    glColor3f(0.9f, 0.7f, 0.3f);

    cubo(
        0.0f, 3.0f, 0.0f,
        1.0f, 1.0f, 1.0f);

    // Brazo izquierdo
    glColor3f(0.8f, 0.3f, 0.3f);

    glPushMatrix();

    // Posición del hombro
    glTranslatef(-1.1f, 2.2f, 0.0f);

    // Rotación del brazo
    glRotatef(anguloBrazo, 0.0f, 0.0f, 1.0f);

    // El brazo se dibuja respecto al hombro
    cubo(
        0.0f, -0.7f, 0.0f,
        0.4f, 1.5f, 0.4f);

    glPopMatrix();

    // Brazo derecho
    glColor3f(0.8f, 0.3f, 0.3f);

    cubo(
        1.1f, 1.5f, 0.0f,
        0.4f, 1.5f, 0.4f);

    // Pierna izquierda
    glColor3f(0.3f, 0.3f, 0.3f);

    cubo(
        -0.45f, -0.3f, 0.0f,
        0.5f, 1.6f, 0.5f);

    // Pierna derecha
    cubo(
        0.45f, -0.3f, 0.0f,
        0.5f, 1.6f, 0.5f);

    glPopMatrix();
}

// Gizmo
void dibujarEjes()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    // Eje X
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);

    // Eje Y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);

    // Eje Z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Cámara
    gluLookAt(
        7, 5, 9,
        0, 1, 0,
        0, 1, 0);

    dibujarEjes();

    dibujarRobot();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'a':
        posicionX -= 0.2f;
        break;

    case 'd':
        posicionX += 0.2f;
        break;

    case 'r':
        anguloBrazo += 10.0f;
        break;

    case 'f':
        anguloBrazo -= 10.0f;
        break;

    case '+':
        escalaRobot += 0.1f;
        break;

    case '-':
        escalaRobot -= 0.1f;

        if (escalaRobot < 0.2f)
            escalaRobot = 0.2f;

        break;

    case 27:
        exit(0);
    }

    glutPostRedisplay();
}

void inicializar()
{
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60.0, 1.0, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
}

// g++ 08-robot.cpp -lGL -lGLU -lglut
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutCreateWindow("Robot 3D - Modelado y Transformaciones");

    inicializar();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);

    glutMainLoop();

    return 0;
}