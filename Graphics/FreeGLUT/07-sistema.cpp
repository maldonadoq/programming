#include <GL/glut.h>
#include <cmath>

float angulo = 0.0f;

void circulo(float radio)
{

    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++)
    {

        float ang = i * 3.14159f / 180.0f;

        glVertex2f(
            radio * cos(ang),
            radio * sin(ang));
    }

    glEnd();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Sol
    circulo(0.15f);

    // Planeta
    glPushMatrix();

    glRotatef(angulo, 0, 0, 1);
    glTranslatef(0.6f, 0.0f, 0.0f);

    glScalef(0.6f, 0.6f, 1);

    circulo(0.15f);

    glPopMatrix();

    glutSwapBuffers();
}

void actualizar(int value)
{

    angulo += 1.0f;

    if (angulo >= 360)
        angulo = 0;

    glutPostRedisplay();

    glutTimerFunc(16, actualizar, 0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutCreateWindow("Sistema Solar");

    glutDisplayFunc(display);

    glutTimerFunc(16, actualizar, 0);

    glutMainLoop();

    return 0;
}