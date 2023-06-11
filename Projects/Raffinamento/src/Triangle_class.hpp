#ifndef Triangle_H
#define Triangle_H

#include <iostream>
#include <Eigen/Eigen>

namespace ProjectLibrary
{
    struct TriMeshStruct; // Dichiarazione forward di TriangularMesh

    struct TriStruct
    {
        unsigned int triID;
        std::array<unsigned int, 3> vertIDs;
        std::array<Eigen::Vector2d, 3> triCoords;
        std::array<unsigned int, 3> edgeIDs;

        TriStruct(unsigned int &triID, std::array<unsigned int, 3> &vertIDs, std::array<Eigen::Vector2d, 3> &triCoords, std::array<unsigned int, 3> &edgeIDs)
            : triID(triID), vertIDs(vertIDs), triCoords(triCoords), edgeIDs(edgeIDs) {}

        TriStruct(unsigned int &id, TriMeshStruct &triMesh);
    };

    class Triangle
    {
        private:
            double area;

        public:
            TriStruct triData;

            Triangle(TriStruct &triData) : triData(triData) {}

            double Area();
    };



    bool operator == (const TriStruct &obj1, const TriStruct &obj2);

    bool descendingOrder(Triangle &a, Triangle &b);

    void sortTris(std::list<Triangle> &triList);
}

#endif // Triangle_H
