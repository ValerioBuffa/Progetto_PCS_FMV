#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include <Eigen/Eigen>

namespace ProjectLibrary
{
    struct TriMeshStruct
    {
        std::vector<unsigned int> cell0DIDs;
        std::vector<Eigen::Vector2d> cell0DCoords;
        std::map<unsigned int, std::list<unsigned int>> cell0DMks;

        std::vector<unsigned int> cell1DIDs;
        std::vector<Eigen::Vector2i> cell1DVerts;
        std::map<unsigned int, std::list<unsigned int>> cell1DMks;

        std::vector<unsigned int> cell2DIDs;
        std::vector<std::array<unsigned int, 3>> cell2DVerts;
        std::vector<std::array<unsigned int, 3>> cell2DEdges;
    };

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

    class TriangularMesh
    {
        private:

        public:
            TriMeshStruct triMeshData;

            TriangularMesh(const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D);

            void Show();
    };

    void fillTriMeshStruct(TriMeshStruct &triMeshData, const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D);

    bool operator == (const TriMeshStruct &obj1, const TriMeshStruct &obj2);

    bool operator == (const TriStruct &obj1, const TriStruct &obj2);

    bool descendingOrder(Triangle &a, Triangle &b);

    void genTris(std::list<Triangle> &triList, TriangularMesh &triMesh);

    void sortTris(std::list<Triangle> &triList);
}

#endif // __EMPTY_H
