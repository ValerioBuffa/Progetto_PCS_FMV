#ifndef TriangularMesh_H
#define TriangularMesh_H

#include "Triangle_class.hpp"
#include <iostream>
#include <Eigen/Eigen>

namespace ProjectLibrary
{
    class Triangle; // Dichiarazione forward di Triangle

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

    void genTris(std::list<Triangle> &triList, TriangularMesh &triMesh);

}

#endif // TriangularMesh_H
