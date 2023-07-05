#ifndef TriangleVector_H
#define TriangleVector_H

#include "Triangle_class.hpp"

namespace ProjectLibrary
{

class TriangleVector
{
private:

public:
    vector<Triangle> triangles;

    TriangleVector();

    TriangleVector(TriangularMesh &triMesh);

    void ShowTriangleVector();

    size_t size();

    Triangle& operator[](size_t index);
};



bool operator == (TriangleVector obj1, TriangleVector obj2);

void heapify(TriangleVector& triangles, int size, int root);

void HeapSortTriangles(TriangleVector& triangles);

}

#endif // TriangleVector_H
