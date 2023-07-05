#ifndef test_Triangle_class_H
#define test_Triangle_class_H

#include <gtest/gtest.h>
#include <unordered_map>
#include "Triangle_class.hpp"

using namespace testing;
using namespace Eigen;
using namespace ProjectLibrary;

TEST(InitTest, TriStructTest)
{
    unsigned int triID = 0;
    array<unsigned int, 3> vertIDs = {0, 1, 2};
    array<unsigned int, 3> edgeIDs = {0, 1, 2};
    array<Vector2d, 3> triCoords = {
            Vector2d(0, 0),
            Vector2d(1, 0),
            Vector2d(1, 1)
    };

    TriStruct triData(triID, vertIDs, triCoords, edgeIDs);


    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell2Ds.csv");

    TriStruct triDataEq(triID, mesh.triMeshData);

    EXPECT_EQ(triData, triDataEq);
}

TEST(MemberTest, TriangleAreaTest)
{
    unsigned int triID = 0;
    array<Vector2d, 3> triCoords = {Vector2d(0, 0), Vector2d(1, 0), Vector2d(1, 1)};
    array<unsigned int, 3> vertIDs = {0, 1, 2};
    array<unsigned int, 3> edgeIDs = {0, 1, 2};

    TriStruct triData(triID, vertIDs, triCoords, edgeIDs);
    Triangle tri(triData);

    EXPECT_EQ(tri.Area(), 0.5);
}

#endif // test_Triangle_class_H
