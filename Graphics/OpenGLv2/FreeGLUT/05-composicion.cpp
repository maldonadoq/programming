#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.4f, 0.2f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 1.5f, 1.0f);

    // glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    // glTranslatef(0.4f, 0.2f, 0.0f);
    // glScalef(1.5f, 1.5f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    glFlush();
}

// g++ 05-composicion.cpp -lGL -lGLU -lglut
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triangulo OpenGL: Composición");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}