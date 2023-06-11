#ifndef test_Triangle_class_H
#define test_Triangle_class_H

#include <gtest/gtest.h>
#include "Triangle_class.hpp"
#include "TriangularMesh_class.hpp"

using namespace testing;

TEST(MemberTest, TriangleAreaTest)
{

    unsigned int triID = 0;
    std::array<Eigen::Vector2d, 3> triCoords = {
        Eigen::Vector2d(0, 0),
        Eigen::Vector2d(1, 0),
        Eigen::Vector2d(1, 1)
    };
    std::array<unsigned int, 3> vertIDs = {0, 1, 2};
    std::array<unsigned int, 3> edgeIDs = {0, 1, 2};

    ProjectLibrary::TriStruct triData(triID, vertIDs, triCoords, edgeIDs);
    ProjectLibrary::Triangle tri(triData);

    EXPECT_EQ(tri.Area(), 0.5);
}

#endif // test_Triangle_class_H
