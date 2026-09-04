#ifndef __PRIMITIVE_FACTORY_HPP__
#define __PRIMITIVE_FACTORY_HPP__

#include "Mesh.hpp"

class PrimitiveFactory
{
public:
    static Geometry cube(float size);
    static Geometry sphere(float radius, int slices, int stacks);
    static Geometry cone(float radius, float height, int segments);
    static Geometry torus(float majorRadius, float minorRadius, int majorSegments, int minorSegments);
    static Geometry grid(int size, float spacing);
    static Geometry line(float x, float y, float z);
};

#endif // __PRIMITIVE_FACTORY_HPP__