#ifndef test_TriangleVector_H
#define test_TriangleVector_H

#include <gtest/gtest.h>
#include <unordered_map>
#include "TriangleVector_class.hpp"

using namespace testing;
using namespace Eigen;
using namespace ProjectLibrary;

TEST(HeapSortTrianglesTest, SortsTrianglesTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    TriangleVector triangles(mesh);
    HeapSortTriangles(triangles);

    for (size_t i = 0; i < triangles.size() - 1; i++)
    {
        EXPECT_TRUE(&triangles[i] <= &triangles[i + 1]);
    }
}

TEST(HeapSortTrianglesTest, SelectsTest)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\GeneralTest\\Cell2Ds.csv");

    TriangleVector triangles(mesh);
    HeapSortTriangles(triangles);

    TriangleVector selectedTriangles = SelecTriangles(triangles, 5);

    vector<double> expectedArea = {0.22, 0.12, 0.12, 0.1, 0.1};

    EXPECT_EQ(selectedTriangles.size(), 5);

    for (int i = 0; i < 5; i++)
    {
        ASSERT_DOUBLE_EQ(selectedTriangles[i].Area(), expectedArea[i]);
    }
}

#endif // test_TriangleVector_H
