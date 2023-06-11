#include "Triangle_class.hpp"
#include "TriangularMesh_class.hpp"

int main(int argc, char* argv[])
{
    try {
        if (argc < 4)
            throw std::runtime_error("Fatal failure: too few arguments");

        if (argc > 4)
            throw std::runtime_error("Fatal failure: too many arguments");

        ProjectLibrary::TriangularMesh mesh(argv[1], argv[2], argv[3]);

        mesh.Show();
    } catch (const std::exception& e){
            return -1;
    }
}
