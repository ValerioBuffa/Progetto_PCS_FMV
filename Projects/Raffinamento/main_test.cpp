#include "test_TriangularMesh_class.hpp"
#include "test_Triangle_class.hpp"
#include "test_TriangleVector_class.hpp"
#include "test_RefineMesh.hpp"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
