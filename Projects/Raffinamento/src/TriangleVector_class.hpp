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

    size_t size() const;

    Triangle& operator[](size_t index);

    const Triangle* begin() const;

    const Triangle* end() const;
};



bool operator == (TriangleVector obj1, TriangleVector obj2);

TriangleVector SelecTriangles(const TriangleVector& triangles, const unsigned int N);

void heapify(TriangleVector& triangles, int size, int root);

void HeapSortTriangles(TriangleVector& triangles);

bool TriangleInVector(const Triangle& triangle, const TriangleVector& removed);

void SemiRefineMesh(TriangularMesh& mesh, Triangle& triangle, TriangleVector& removed);

}

#endif // TriangleVector_H
