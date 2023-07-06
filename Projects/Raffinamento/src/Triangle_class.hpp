#ifndef Triangle_H
#define Triangle_H

#include "TriangularMesh_class.hpp"

namespace ProjectLibrary
{

struct TriStruct
{
    unsigned int triID;
    array<Vector2d, 3> triCoords;

    TriStruct(unsigned int &triID, array<Vector2d, 3> &triCoords) : triID(triID), triCoords(triCoords) {}

    TriStruct(unsigned int &id, TriMeshStruct &triMesh);
};

class Triangle
{
    private:

    public:       
        TriStruct triData;

        Triangle(TriStruct &triData) : triData(triData) {}

        void Show();

        double Area();
};



bool operator == (const TriStruct &obj1, const TriStruct &obj2);

bool operator != (const TriStruct &obj1, const TriStruct &obj2);

bool operator == (const Triangle &obj1, const Triangle &obj2);

bool operator > (Triangle &obj1, Triangle &obj2);

bool operator >= (Triangle &obj1, Triangle &obj2);

bool operator < (Triangle &obj1, Triangle &obj2);

bool operator <= (Triangle &obj1, Triangle &obj2);

}

#endif // Triangle_H
