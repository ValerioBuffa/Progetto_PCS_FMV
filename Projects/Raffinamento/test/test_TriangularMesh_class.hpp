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

    TriStruct triData0(triID0, triCoords0);
    Triangle tri0(triData0);
    triangles0.triangles.push_back(tri0);

    unsigned int triID1 = 1;
    array<Vector2d, 3> triCoords1 = {Vector2d(0, 0), Vector2d(1, 1), Vector2d(0, 1)};

    TriStruct triData1(triID1, triCoords1);
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

TEST(EdgeTest, EdgeLengthTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    double Length0 = mesh.EdgeLength(4);
    double expectedLength0 = 0.44721359549995798;

    double Length1 = mesh.EdgeLength(11);
    double expectedLength1 = 0.44721359549995798;

    double Length2 = mesh.EdgeLength(16);
    double expectedLength2 = 0.4;

    ASSERT_DOUBLE_EQ(Length0, expectedLength0);
    ASSERT_DOUBLE_EQ(Length1, expectedLength1);
    ASSERT_DOUBLE_EQ(Length2, expectedLength2);
}

TEST(EdgeTest, EdgeMaxTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    unsigned int maxEdge0 = mesh.MaxEdge(2);
    unsigned int expectedmaxEdge0 = 1;

    unsigned int maxEdge1 = mesh.MaxEdge(5);
    unsigned int expectedmaxEdge1 = 14;

    unsigned int maxEdge2 = mesh.MaxEdge(8);
    unsigned int expectedmaxEdge2 = 16;


    ASSERT_DOUBLE_EQ(maxEdge0, expectedmaxEdge0);
    ASSERT_DOUBLE_EQ(maxEdge1, expectedmaxEdge1);
    ASSERT_DOUBLE_EQ(maxEdge2, expectedmaxEdge2);
}

#endif // test_TriangularMesh_class_H
