#include "PrimitiveFactory.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Geometry PrimitiveFactory::cube(float size)
{
    float h = size / 2.0f;

    Geometry g;

    g.vertices = {
        -h, -h, -h,
        h, -h, -h,
        h, h, -h,
        -h, h, -h,

        -h, -h, h,
        h, -h, h,
        h, h, h,
        -h, h, h};

    g.indices = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7};

    return g;
}

Geometry PrimitiveFactory::sphere(float radius, int slices, int stacks)
{
    Geometry g;

    for (int stack = 0; stack <= stacks; stack++)
    {
        float v = static_cast<float>(stack) / stacks;
        float phi = glm::pi<float>() * (v - 0.5f);

        float y = radius * std::sin(phi);
        float r = radius * std::cos(phi);

        for (int slice = 0; slice < slices; slice++)
        {
            float u = static_cast<float>(slice) / slices;
            float theta = glm::two_pi<float>() * u;

            float x = r * std::cos(theta);
            float z = r * std::sin(theta);

            g.vertices.push_back(x);
            g.vertices.push_back(y);
            g.vertices.push_back(z);
        }
    }

    for (int stack = 0; stack <= stacks; stack++)
    {
        for (int slice = 0; slice < slices; slice++)
        {
            int current = stack * slices + slice;
            int nextSlice = stack * slices + (slice + 1) % slices;

            g.indices.push_back(current);
            g.indices.push_back(nextSlice);
        }
    }

    for (int stack = 0; stack < stacks; stack++)
    {
        for (int slice = 0; slice < slices; slice++)
        {
            int current = stack * slices + slice;
            int nextStack = (stack + 1) * slices + slice;

            g.indices.push_back(current);
            g.indices.push_back(nextStack);
        }
    }

    return g;
}

Geometry PrimitiveFactory::cone(float radius, float height, int segments)
{
    Geometry g;

    for (int i = 0; i < segments; i++)
    {
        float angle = glm::two_pi<float>() * static_cast<float>(i) / segments;

        g.vertices.push_back(radius * std::cos(angle));
        g.vertices.push_back(0.0f);
        g.vertices.push_back(radius * std::sin(angle));
    }

    unsigned int top = segments;

    g.vertices.push_back(0.0f);
    g.vertices.push_back(height);
    g.vertices.push_back(0.0f);

    for (int i = 0; i < segments; i++)
    {
        int next = (i + 1) % segments;

        g.indices.push_back(i);
        g.indices.push_back(next);

        g.indices.push_back(i);
        g.indices.push_back(top);
    }

    return g;
}

Geometry PrimitiveFactory::torus(float majorRadius, float minorRadius, int majorSegments, int minorSegments)
{
    Geometry g;

    for (int i = 0; i < majorSegments; i++)
    {
        float u = glm::two_pi<float>() * static_cast<float>(i) / majorSegments;

        for (int j = 0; j < minorSegments; j++)
        {
            float v = glm::two_pi<float>() * static_cast<float>(j) / minorSegments;

            float x = (majorRadius + minorRadius * std::cos(v)) * std::cos(u);
            float y = minorRadius * std::sin(v);
            float z = (majorRadius + minorRadius * std::cos(v)) * std::sin(u);

            g.vertices.push_back(x);
            g.vertices.push_back(y);
            g.vertices.push_back(z);
        }
    }

    for (int i = 0; i < majorSegments; i++)
    {
        for (int j = 0; j < minorSegments; j++)
        {
            int current = i * minorSegments + j;
            int nextMinor = i * minorSegments + (j + 1) % minorSegments;
            int nextMajor = ((i + 1) % majorSegments) * minorSegments + j;

            g.indices.push_back(current);
            g.indices.push_back(nextMinor);

            g.indices.push_back(current);
            g.indices.push_back(nextMajor);
        }
    }

    return g;
}

Geometry PrimitiveFactory::grid(int size, float spacing)
{
    Geometry g;
    unsigned int index = 0;

    for (int i = -size; i <= size; i++)
    {
        float value = i * spacing;

        g.vertices.push_back(value);
        g.vertices.push_back(0.0f);
        g.vertices.push_back(-size * spacing);

        g.vertices.push_back(value);
        g.vertices.push_back(0.0f);
        g.vertices.push_back(size * spacing);

        g.indices.push_back(index++);
        g.indices.push_back(index++);

        g.vertices.push_back(-size * spacing);
        g.vertices.push_back(0.0f);
        g.vertices.push_back(value);

        g.vertices.push_back(size * spacing);
        g.vertices.push_back(0.0f);
        g.vertices.push_back(value);

        g.indices.push_back(index++);
        g.indices.push_back(index++);
    }

    return g;
}

Geometry PrimitiveFactory::line(float x, float y, float z)
{
    Geometry g;

    g.vertices = {
        0.0f, 0.0f, 0.0f,
        x, y, z};

    g.indices = {0, 1};

    return g;
}