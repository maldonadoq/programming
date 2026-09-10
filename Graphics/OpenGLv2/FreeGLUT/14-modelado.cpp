#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

struct Vec3
{
    float x, y, z;
};

struct Face
{
    int a, b, c;
};

// =====================================================
// Clase OBJModel
// =====================================================

class OBJModel
{
private:
    std::vector<Vec3> vertices;
    std::vector<Face> faces;

    float rotY = 0.0f;
    float scale = 1.0f;

public:
    bool load(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cout << "No se pudo abrir " << filename << std::endl;
            return false;
        }

        std::string line;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);

            std::string type;
            ss >> type;

            if (type == "v")
            {
                Vec3 v;
                ss >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            }

            else if (type == "f")
            {
                Face f;
                ss >> f.a >> f.b >> f.c;

                f.a--;
                f.b--;
                f.c--;

                faces.push_back(f);
            }
        }

        std::cout << "Modelo cargado correctamente" << std::endl;
        std::cout << "Vertices: " << vertices.size() << std::endl;
        std::cout << "Caras: " << faces.size() << std::endl;

        return true;
    }

    void draw()
    {
        glPushMatrix();

        glRotatef(rotY, 0.0f, 1.0f, 0.0f);
        glScalef(scale, scale, scale);

        glColor3f(0.2f, 0.6f, 1.0f);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);

        for (const Face &f : faces)
        {
            Vec3 v1 = vertices[f.a];
            Vec3 v2 = vertices[f.b];
            Vec3 v3 = vertices[f.c];

            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glVertex3f(v3.x, v3.y, v3.z);
        }

        glEnd();

        glPopMatrix();
    }

    void rotate(float angle)
    {
        rotY += angle;
    }

    void changeScale(float value)
    {
        scale += value;

        if (scale < 0.1f)
        {
            scale = 0.1f;
        }
    }
};

// =====================================================
// Clase Camera
// =====================================================

class Camera
{
private:
    float x = 0.0f;
    float y = 2.0f;
    float z = 7.0f;

public:
    void apply()
    {
        gluLookAt(
            x, y, z,
            0.0f, 0.5f, 0.0f,
            0.0f, 1.0f, 0.0f);
    }

    void moveX(float value)
    {
        x += value;
    }

    void moveZ(float value)
    {
        z += value;
    }
};

// =====================================================
// Clase Application
// =====================================================

class Application
{
private:
    static Application *instance;

    OBJModel model;
    Camera camera;

public:
    bool initialize(int argc, char **argv)
    {
        instance = this;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(900, 600);
        glutCreateWindow("OBJ Viewer - OpenGL");

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f);

        std::string modelPath = "modelo2.obj";
        if (!model.load(modelPath))
        {
            return false;
        }

        glutDisplayFunc(displayCallback);
        glutReshapeFunc(reshapeCallback);
        glutKeyboardFunc(keyboardCallback);

        return true;
    }

    void run()
    {
        glutMainLoop();
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        camera.apply();

        // Piso
        glColor3f(0.7f, 0.7f, 0.7f);

        glBegin(GL_QUADS);
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 0.0f, 5.0f);
        glVertex3f(5.0f, 0.0f, 5.0f);
        glVertex3f(5.0f, 0.0f, -5.0f);
        glEnd();

        model.draw();

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
            (float)w / h,
            0.1,
            100.0);

        glMatrixMode(GL_MODELVIEW);
    }

    void keyboard(unsigned char key)
    {
        switch (key)
        {
        case 'a':
            camera.moveX(-0.3f);
            break;

        case 'd':
            camera.moveX(0.3f);
            break;

        case 'w':
            camera.moveZ(-0.3f);
            break;

        case 's':
            camera.moveZ(0.3f);
            break;

        case 'j':
            model.rotate(-5.0f);
            break;

        case 'l':
            model.rotate(5.0f);
            break;

        case '+':
            model.changeScale(0.1f);
            break;

        case '-':
            model.changeScale(-0.1f);
            break;

        case 27:
            std::exit(0);
        }

        glutPostRedisplay();
    }

    static void displayCallback()
    {
        instance->display();
    }

    static void reshapeCallback(int w, int h)
    {
        instance->reshape(w, h);
    }

    static void keyboardCallback(
        unsigned char key,
        int x,
        int y)
    {
        instance->keyboard(key);
    }
};

Application *Application::instance = nullptr;

// =====================================================
// main
// =====================================================

int main(int argc, char **argv)
{
    Application app;

    if (!app.initialize(argc, argv))
    {
        return 1;
    }

    app.run();

    return 0;
}