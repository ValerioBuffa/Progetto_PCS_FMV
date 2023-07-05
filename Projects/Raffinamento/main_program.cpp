#include "TriangularMesh_class.hpp"
#include "Triangle_class.hpp"
#include "TriangleVector_class.hpp"

using namespace ProjectLibrary;

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 4)
            throw runtime_error("Fatal failure: too few arguments");

        if (argc > 4)
            throw runtime_error("Fatal failure: too many arguments");

        TriangularMesh mesh(argv[1], argv[2], argv[3]);

        mesh.Show();

        TriangleVector triangles(mesh);

        HeapSortTriangles(triangles);
        cout << "Sort:" << endl;
        triangles.ShowTriangleVector();

        vector<unsigned int> adj = mesh.GetAdjacentTriangles(94);
        cout << adj[0] << "   " << adj [1] << endl;
    }
    catch (const exception& e)
    {
        return -1;
    }
}
