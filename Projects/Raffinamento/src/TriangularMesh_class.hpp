#ifndef TriangularMesh_H
#define TriangularMesh_H

#include <iostream>
#include <Eigen/Eigen>
#include <unordered_map>

using namespace std;
using namespace Eigen;

namespace ProjectLibrary
{

struct TriMeshStruct
{
    vector<unsigned int> cell0DIDs;
    vector<Vector2d> cell0DCoords;
    vector<unsigned int> cell0DMks;

    vector<unsigned int> cell1DIDs;
    vector<Vector2i> cell1DVerts;
    vector<unsigned int> cell1DMks;

    vector<unsigned int> cell2DIDs;
    vector<array<unsigned int, 3>> cell2DVerts;
    vector<array<unsigned int, 3>> cell2DEdges;
    vector<unsigned int> cell2DMks;
};

class TriangularMesh
{
    private:
        unordered_map<unsigned int, vector<unsigned int>> adjacentTriangles;
    public:
        TriMeshStruct triMeshData;

        TriangularMesh(const string& filePath0D, const string& filePath1D, const string& filePath2D);

        void Show();

        vector<unsigned int> GetAdjacentTriangles(unsigned int edgeId);

        void PrintToCSV(const string& filePath0, const string& filePath1, const string& filePath2);

        void CreatePoint(const unsigned int& cell0DID, const Vector2d& cell0DCoord, const unsigned int& cell0DMk);

        void CreateEdge(const unsigned int& cell1DID, const Vector2i& cell1DVert, const unsigned int& cell1DMk);

        void UpdateEdge(const unsigned int& cell1DID, const Vector2i& cell1DVert, const unsigned int& cell1DMk);

        void CreateTriangle(const unsigned int& cell2DID, const array<unsigned int, 3>& cell2DVerts, const array<unsigned int, 3>& cell2DEdges, const unsigned int& cell2DMk);

        void UpdateTriangle(const unsigned int& cell2DID, const array<unsigned int, 3>& cell2DVerts, const array<unsigned int, 3>& cell2DEdges, const unsigned int& cell2DMk);

        double EdgeLength(const unsigned int& cell1DID);

        unsigned int MaxEdge(const unsigned int& cell2DID);

        Vector2d MidPoint(const unsigned int& cell1DID);

        void Bisection(const unsigned int& cell2DID, unsigned int& newcell2DID, const unsigned int& cell1DID,
                       const unsigned int& cell2DID2, unsigned int& newcell2DID2, const unsigned int& cell1DID2,
                       unsigned int& midpoint, const unsigned int& mode);

};



bool operator == (const TriMeshStruct &obj1, const TriMeshStruct &obj2);

void fillTriMeshStruct(TriMeshStruct &triMeshData, unordered_map<unsigned int, vector<unsigned int>> &adjacentTriangles , const string &filePath0D, const string &filePath1D, const string &filePath2D);

void PrintToCSV0(const string& filePathOut0, TriMeshStruct &triMeshData);

void PrintToCSV1(const string& filePathOut1, TriMeshStruct &triMeshData);

void PrintToCSV2(const string& filePathOut2, TriMeshStruct &triMeshData);

int ToRefine(TriangularMesh& mesh, const double n);

void Refine(TriangularMesh& mesh, const unsigned int N);

}

#endif // TriangularMesh_H
