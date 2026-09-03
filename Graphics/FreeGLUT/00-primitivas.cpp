#include <GL/glut.h>

// OpenGL V2
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // TRIÁNGULO
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.5f, 0.8f);
    glEnd();

    // CUADRADO
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.2f, 0.7f);
    glEnd();

    // LÍNEA
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(10.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(0.8f, -0.5f);
    glEnd();

    // PUNTOS
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);

    glBegin(GL_POINTS);
    glVertex2f(-0.5f, -0.8f);
    glVertex2f(0.0f, -0.8f);
    glVertex2f(0.5f, -0.8f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(700, 600);
    glutCreateWindow("Primitivas OpenGL");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}