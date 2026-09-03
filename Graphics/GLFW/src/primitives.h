#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <OpenGL/glu.h>
#include <cmath>

#define PPI 3.14159265f

// =====================================================
// PRIMITIVAS
// =====================================================

class Primitivas
{
public:
    static void cubo(float lado)
    {
        float h = lado / 2.0f;

        float vertices[8][3] = {
            {-h, -h, -h},
            {h, -h, -h},
            {h, h, -h},
            {-h, h, -h},

            {-h, -h, h},
            {h, -h, h},
            {h, h, h},
            {-h, h, h}};

        int aristas[12][2] = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 0},

            {4, 5},
            {5, 6},
            {6, 7},
            {7, 4},

            {0, 4},
            {1, 5},
            {2, 6},
            {3, 7}};

        glBegin(GL_LINES);

        for (int i = 0; i < 12; i++)
        {
            int a = aristas[i][0];
            int b = aristas[i][1];

            glVertex3fv(vertices[a]);
            glVertex3fv(vertices[b]);
        }

        glEnd();
    }

    static void esfera(
        float radio,
        int sectores = 18,
        int niveles = 12)
    {
        for (int i = 1; i < niveles; i++)
        {
            float phi =
                PPI * i / niveles -
                PPI / 2.0f;

            float y =
                radio * std::sin(phi);

            float r =
                radio * std::cos(phi);

            glBegin(GL_LINE_LOOP);

            for (int j = 0; j < sectores; j++)
            {
                float theta =
                    2.0f *
                    PPI *
                    j /
                    sectores;

                glVertex3f(
                    r * std::cos(theta),
                    y,
                    r * std::sin(theta));
            }

            glEnd();
        }

        for (int j = 0; j < sectores; j++)
        {
            float theta =
                2.0f *
                PPI *
                j /
                sectores;

            glBegin(GL_LINE_STRIP);

            for (int i = 0; i <= niveles; i++)
            {
                float phi =
                    PPI * i / niveles -
                    PPI / 2.0f;

                glVertex3f(
                    radio *
                        std::cos(phi) *
                        std::cos(theta),

                    radio *
                        std::sin(phi),

                    radio *
                        std::cos(phi) *
                        std::sin(theta));
            }

            glEnd();
        }
    }

    static void cono(
        float radio,
        float altura,
        int segmentos = 18)
    {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < segmentos; i++)
        {
            float angulo =
                2.0f *
                PPI *
                i /
                segmentos;

            glVertex3f(
                radio * std::cos(angulo),
                0,
                radio * std::sin(angulo));
        }

        glEnd();

        glBegin(GL_LINES);

        for (int i = 0; i < segmentos; i++)
        {
            float angulo =
                2.0f *
                PPI *
                i /
                segmentos;

            glVertex3f(
                radio * std::cos(angulo),
                0,
                radio * std::sin(angulo));

            glVertex3f(
                0,
                altura,
                0);
        }

        glEnd();
    }

    static void torus(
        float radioInterno,
        float radioExterno,
        int lados = 12,
        int anillos = 24)
    {
        for (int i = 0; i < anillos; i++)
        {
            float theta =
                2.0f *
                PPI *
                i /
                anillos;

            glBegin(GL_LINE_LOOP);

            for (int j = 0; j < lados; j++)
            {
                float phi =
                    2.0f *
                    PPI *
                    j /
                    lados;

                float r =
                    radioExterno +
                    radioInterno *
                        std::cos(phi);

                glVertex3f(
                    r * std::cos(theta),
                    radioInterno * std::sin(phi),
                    r * std::sin(theta));
            }

            glEnd();
        }
    }
};

#endif