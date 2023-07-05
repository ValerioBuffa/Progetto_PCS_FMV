#ifndef test_TriangleVector_H
#define test_TriangleVector_H

#include <gtest/gtest.h>
#include <unordered_map>
#include "TriangularMesh_class.hpp"
#include "Triangle_class.hpp"
#include "TriangleVector_class.hpp"

using namespace testing;
using namespace Eigen;
using namespace ProjectLibrary;

TEST(HeapSortTrianglesTest, SortsTrianglesInAscendingOrder)
{
    TriangularMesh mesh("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\SortingTest\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\SortingTest\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\SortingTest\\Cell2Ds.csv");

    TriangleVector triangles(mesh);
    HeapSortTriangles(triangles);

    for (size_t i = 0; i < triangles.size() - 1; i++)
    {
        EXPECT_TRUE(&triangles[i] <= &triangles[i + 1]);
    }
}

#endif // test_TriangleVector_H
