#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glScalef(2.0f, 0.5f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    glFlush();
}

// g++ 04-escala.cpp -lGL -lGLU -lglut
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triangulo OpenGL: Escala");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}