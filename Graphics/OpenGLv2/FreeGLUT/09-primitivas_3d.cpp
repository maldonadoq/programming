#include <GL/glut.h>

// Ángulo para observar mejor los objetos
float angulo = 25.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Cámara 3D
    gluLookAt(
        0.0, 3.0, 12.0,   // posición de la cámara
        0.0, 0.0, 0.0,    // punto observado
        0.0, 1.0, 0.0     // dirección vertical
    );

    // Rotación general para apreciar la profundidad
    glRotatef(angulo, 0.0f, 1.0f, 0.0f);


    // =====================================
    // CUBO
    // =====================================
    glPushMatrix();

        glTranslatef(-3.5f, 0.0f, 0.0f);

        glColor3f(1.0f, 0.2f, 0.2f);

        glutWireCube(1.5);

    glPopMatrix();


    // =====================================
    // ESFERA
    // =====================================
    glPushMatrix();

        glTranslatef(-1.2f, 0.0f, 0.0f);

        glColor3f(0.2f, 0.8f, 0.3f);

        glutWireSphere(
            0.8,   // radio
            30,    // slices
            30     // stacks
        );

    glPopMatrix();


    // =====================================
    // CONO
    // =====================================
    glPushMatrix();

        glTranslatef(1.2f, -0.7f, 0.0f);

        // El cono de GLUT crece sobre Z.
        // Lo rotamos para colocarlo vertical.
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.2f, 0.4f, 1.0f);

        glutWireCone(
            0.8,   // radio
            1.8,   // altura
            30,
            30
        );

    glPopMatrix();


    // =====================================
    // TOROIDE
    // =====================================
    glPushMatrix();

        glTranslatef(3.5f, 0.0f, 0.0f);

        glRotatef(65.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(1.0f, 0.7f, 0.1f);

        glutWireTorus(
            0.20,  // radio interno
            0.70,  // radio externo
            30,
            30
        );

    glPopMatrix();


    glutSwapBuffers();
}


// =====================================
// TECLADO
// =====================================
void teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 'a')
        angulo -= 5.0f;

    if (tecla == 'd')
        angulo += 5.0f;

    glutPostRedisplay();
}


// =====================================
// INICIALIZACIÓN
// =====================================
void inicializar()
{
    // Fondo negro
    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );

    // Fundamental para trabajar en 3D
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Proyección perspectiva
    gluPerspective(
        60.0,
        1.0,
        1.0,
        50.0
    );

    glMatrixMode(GL_MODELVIEW);
}


// =====================================
// MAIN
// =====================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(900, 600);

    glutCreateWindow(
        "Primitivas geometricas 3D"
    );

    inicializar();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);

    glutMainLoop();

    return 0;
}