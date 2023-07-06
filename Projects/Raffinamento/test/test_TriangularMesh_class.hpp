#ifndef test_TriangularMesh_class_H
#define test_TriangularMesh_class_H

#include <gtest/gtest.h>
#include "TriangleVector_class.hpp"

using namespace testing;
using namespace Eigen;
using namespace ProjectLibrary;

TEST(InitTest, InitTriMeshStructTest)
{
    TriMeshStruct triMeshData;

    triMeshData.cell0DIDs = {0, 1, 2, 3};

    triMeshData.cell0DCoords.push_back(Vector2d(0.0, 0.0));
    triMeshData.cell0DCoords.push_back(Vector2d(1.0, 0.0));
    triMeshData.cell0DCoords.push_back(Vector2d(1.0, 1.0));
    triMeshData.cell0DCoords.push_back(Vector2d(0.0, 1.0));

    triMeshData.cell0DMks = {1, 2, 3, 3};


    triMeshData.cell1DIDs = {0, 1, 2, 3, 4};

    triMeshData.cell1DVerts.push_back(Vector2i(0, 1));
    triMeshData.cell1DVerts.push_back(Vector2i(1, 2));
    triMeshData.cell1DVerts.push_back(Vector2i(0, 2));
    triMeshData.cell1DVerts.push_back(Vector2i(2, 3));
    triMeshData.cell1DVerts.push_back(Vector2i(0, 3));

    triMeshData.cell1DMks = {1, 1, 2, 3, 3};


    triMeshData.cell2DIDs = {0, 1};

    triMeshData.cell2DVerts.push_back({0, 1, 2});
    triMeshData.cell2DVerts.push_back({0, 2, 3});

    triMeshData.cell2DEdges.push_back({0, 1, 2});
    triMeshData.cell2DEdges.push_back({2, 3, 4});

    triMeshData.cell2DMks = {0, 0};


    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell2Ds.csv");

    EXPECT_EQ(triMeshData, mesh.triMeshData);
}

TEST(TriangleVector, TriangleVectorTest)
{
    TriangleVector triangles0;

    unsigned int triID0 = 0;
    array<Vector2d, 3> triCoords0 = {Vector2d(0, 0), Vector2d(1, 0), Vector2d(1, 1)};
    array<unsigned int, 3> vertIDs0 = {0, 1, 2};
    array<unsigned int, 3> edgeIDs0 = {0, 1, 2};

    TriStruct triData0(triID0, vertIDs0, triCoords0, edgeIDs0);
    Triangle tri0(triData0);
    triangles0.triangles.push_back(tri0);

    unsigned int triID1 = 1;
    array<Vector2d, 3> triCoords1 = {Vector2d(0, 0), Vector2d(1, 1), Vector2d(0, 1)};
    array<unsigned int, 3> vertIDs1 = {0, 2, 3};
    array<unsigned int, 3> edgeIDs1 = {2, 3, 4};

    TriStruct triData1(triID1, vertIDs1, triCoords1, edgeIDs1);
    Triangle tri1(triData1);
    triangles0.triangles.push_back(tri1);

    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell2Ds.csv");

    TriangleVector triangles1(mesh);

    EXPECT_EQ(2, triangles1.size());
    EXPECT_EQ(mesh.triMeshData.cell2DIDs.size(), triangles1.size());
    EXPECT_EQ(triangles0, triangles1);
}

TEST(AdjacentTrianglesTest, GetAdjacentTrianglesTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    ASSERT_TRUE(mesh.GetAdjacentTriangles(10)[0] == 5 || mesh.GetAdjacentTriangles(10)[1] == 6);
}

#endif // test_TriangularMesh_class_H
