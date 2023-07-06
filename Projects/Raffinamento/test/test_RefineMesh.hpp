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

#endif // test_RefineMesh_H
