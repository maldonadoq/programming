#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    glFlush();
}

// g++ 03-rotacion.cpp -lGL -lGLU -lglut
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triangulo OpenGL: Rotación");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}