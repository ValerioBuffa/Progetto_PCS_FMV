#ifndef test_RefineMesh_H
#define test_RefineMesh_H

#include <gtest/gtest.h>
#include "TriangularMesh_class.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(RefineMeshTest, ToRefineTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    double n0 = 0.5;
    int expected0 = 5;
    int result0 = ToRefine(mesh, n0);

    double n1 = 0.8;
    int expected1 = 8;
    int result1 = ToRefine(mesh, n1);

    EXPECT_EQ(result0, expected0);
    EXPECT_EQ(result1, expected1);
}

TEST(RefineMeshTest, RefineCase1Test)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Input\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Input\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Input\\Cell2Ds.csv");

    TriangularMesh expectedmesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Output\\Cell0Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Output\\Cell1Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case1\\Output\\Cell2Ds.csv");

    int N = ToRefine(mesh, 1);
    Refine(mesh, N);

    EXPECT_EQ(mesh.triMeshData, expectedmesh.triMeshData);
    for (size_t i = 0; i < mesh.triMeshData.cell2DIDs.size(); ++i)
    {
        unsigned int ID = mesh.triMeshData.cell2DIDs[i];

        // Ottieni le mappe adjacentTriangles per gli ID correnti
        const auto& adjTriangles1 = mesh.GetAdjacentTriangles(ID);
        const auto& adjTriangles2 = expectedmesh.GetAdjacentTriangles(ID);

        // Confronta le mappe adjacentTriangles
        EXPECT_EQ(adjTriangles1, adjTriangles2);
    }
}

TEST(RefineMeshTest, RefineCase2Test)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Input\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Input\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Input\\Cell2Ds.csv");

    TriangularMesh expectedmesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Output\\Cell0Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Output\\Cell1Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case2\\Output\\Cell2Ds.csv");

    int N = ToRefine(mesh, 0.5);
    Refine(mesh, N);

    EXPECT_EQ(mesh.triMeshData, expectedmesh.triMeshData);
    for (size_t i = 0; i < mesh.triMeshData.cell2DIDs.size(); ++i)
    {
        unsigned int ID = mesh.triMeshData.cell2DIDs[i];

        // Ottieni le mappe adjacentTriangles per gli ID correnti
        const auto& adjTriangles1 = mesh.GetAdjacentTriangles(ID);
        const auto& adjTriangles2 = expectedmesh.GetAdjacentTriangles(ID);

        // Confronta le mappe adjacentTriangles
        EXPECT_EQ(adjTriangles1, adjTriangles2);
    }
}

TEST(RefineMeshTest, RefineCase3_1Test)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Input\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Input\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Input\\Cell2Ds.csv");

    TriangularMesh expectedmesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Output\\Cell0Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Output\\Cell1Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_1\\Output\\Cell2Ds.csv");

    int N = ToRefine(mesh, 0.5);
    Refine(mesh, N);

    EXPECT_EQ(mesh.triMeshData, expectedmesh.triMeshData);
    for (size_t i = 0; i < mesh.triMeshData.cell2DIDs.size(); ++i)
    {
        unsigned int ID = mesh.triMeshData.cell2DIDs[i];

        // Ottieni le mappe adjacentTriangles per gli ID correnti
        const auto& adjTriangles1 = mesh.GetAdjacentTriangles(ID);
        const auto& adjTriangles2 = expectedmesh.GetAdjacentTriangles(ID);

        // Confronta le mappe adjacentTriangles
        EXPECT_EQ(adjTriangles1, adjTriangles2);
    }
}

TEST(RefineMeshTest, RefineCase3_2Test)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Input\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Input\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Input\\Cell2Ds.csv");

    TriangularMesh expectedmesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Output\\Cell0Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Output\\Cell1Ds.csv",
                                "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Case3_2\\Output\\Cell2Ds.csv");

    int N = ToRefine(mesh, 0.5);
    Refine(mesh, N);

    EXPECT_EQ(mesh.triMeshData, expectedmesh.triMeshData);
    for (size_t i = 0; i < mesh.triMeshData.cell2DIDs.size(); ++i)
    {
        unsigned int ID = mesh.triMeshData.cell2DIDs[i];

        // Ottieni le mappe adjacentTriangles per gli ID correnti
        const auto& adjTriangles1 = mesh.GetAdjacentTriangles(ID);
        const auto& adjTriangles2 = expectedmesh.GetAdjacentTriangles(ID);

        // Confronta le mappe adjacentTriangles
        EXPECT_EQ(adjTriangles1, adjTriangles2);
    }
}

#endif // test_RefineMesh_H
