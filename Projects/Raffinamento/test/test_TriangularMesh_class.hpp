#ifndef test_TriangularMesh_class_H
#define test_TriangularMesh_class_H

#include <gtest/gtest.h>
#include "Triangle_class.hpp"
#include "TriangularMesh_class.hpp"

using namespace testing;

TEST(InitTest, InitTriMeshStructTest)
{
    ProjectLibrary::TriMeshStruct triMeshData;

    triMeshData.cell0DIDs = {0, 1, 2, 3};

    triMeshData.cell0DCoords.push_back(Eigen::Vector2d(0.0, 0.0));
    triMeshData.cell0DCoords.push_back(Eigen::Vector2d(1.0, 0.0));
    triMeshData.cell0DCoords.push_back(Eigen::Vector2d(1.0, 1.0));
    triMeshData.cell0DCoords.push_back(Eigen::Vector2d(0.0, 1.0));

    triMeshData.cell0DMks[1] = {0};
    triMeshData.cell0DMks[2] = {1};
    triMeshData.cell0DMks[3] = {2, 3};

    triMeshData.cell1DIDs = {0, 1, 2, 3, 4};

    triMeshData.cell1DVerts.push_back(Eigen::Vector2i(0, 1));
    triMeshData.cell1DVerts.push_back(Eigen::Vector2i(1, 2));
    triMeshData.cell1DVerts.push_back(Eigen::Vector2i(0, 2));
    triMeshData.cell1DVerts.push_back(Eigen::Vector2i(2, 3));
    triMeshData.cell1DVerts.push_back(Eigen::Vector2i(0, 3));

    triMeshData.cell1DMks[1] = {0, 1};
    triMeshData.cell1DMks[2] = {2};
    triMeshData.cell1DMks[3] = {3, 4};

    triMeshData.cell2DIDs = {0, 1};

    triMeshData.cell2DVerts.push_back({0, 1, 2});
    triMeshData.cell2DVerts.push_back({0, 2, 3});

    triMeshData.cell2DEdges.push_back({0, 1, 2});
    triMeshData.cell2DEdges.push_back({2, 3, 4});

    ProjectLibrary::TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell0Ds.csv",
                                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell1Ds.csv",
                                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell2Ds.csv");

    EXPECT_EQ(triMeshData, mesh.triMeshData);
}

TEST(InitTest, TriStructTest)
{
    unsigned int triID = 0;
    std::array<unsigned int, 3> vertIDs = {0, 1, 2};
    std::array<unsigned int, 3> edgeIDs = {0, 1, 2};
    std::array<Eigen::Vector2d, 3> triCoords = {
        Eigen::Vector2d(0, 0),
        Eigen::Vector2d(1, 0),
        Eigen::Vector2d(1, 1)
    };

    ProjectLibrary::TriStruct triData(triID, vertIDs, triCoords, edgeIDs);

    ProjectLibrary::TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell0Ds.csv",
                                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell1Ds.csv",
                                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\InitMeshTest\\Cell2Ds.csv");

    ProjectLibrary::TriStruct triDataEq(triID, mesh.triMeshData);

    EXPECT_EQ(triData, triDataEq);
}

#endif // test_TriangularMesh_class_H
