#include <GL/glut.h>

void dibujarCasa()
{
    // Cuerpo
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.4f);
    glVertex2f(0.4f, -0.4f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Techo
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(0.5f, 0.2f);
    glVertex2f(0.0f, 0.7f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.3f, 0.1f, 0.0f);
    glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.7f, 1.0f);

    dibujarCasa();

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Transformaciones - Casa");

    // glClearColor(1, 1, 1, 1);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}