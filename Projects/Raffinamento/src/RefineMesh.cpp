#include "TriangleVector_class.hpp"

namespace ProjectLibrary
{


//Questa funzione ci dice quanti triangoli bisogna raffinare in base al numero totale di triangoli e un parametro che ha valori tra 0 e 1
int ToRefine(TriangularMesh& mesh, const double n)
{
    size_t TOT = mesh.triMeshData.cell2DIDs.size();
    return int(TOT * n);
}


//Verifica se il triangolo è presente nel vettore removed
bool TriangleInVector(const Triangle& triangle, const TriangleVector& removed)
{
    for (const auto& removedTriangle : removed)
    {
        if (removedTriangle == triangle)
        {
            return true;
        }
    }
    return false;
}


//Questa è la funzione che esegue il refine
void Refine(TriangularMesh& mesh, const unsigned int N)
{
    TriangleVector triangles(mesh);
    HeapSortTriangles(triangles);
    TriangleVector selectedTriangles = SelecTriangles(triangles, N);
    TriangleVector removed;

    for (size_t i = 0; i < selectedTriangles.size(); i++)
    {
        Triangle triangle = selectedTriangles[i];

        if (TriangleInVector(triangle, removed))
        {
            i++;
            continue;  // Salta l'iterazione se il triangolo è presente in removed
        }

        SemiRefineMesh(mesh, triangle, removed);
    }
}


//Questa funzione
void SemiRefineMesh(TriangularMesh& mesh, Triangle& triangle, TriangleVector& removed)
{
    unsigned int flag = 0;
    while(flag == 0)
    {
        unsigned int lT1 = 0;
        if (flag == 0)
        {
            unsigned int T1 = triangle.triData.triID;
            unsigned int lT1 = mesh.MaxEdge(T1);
        }
        else if(flag == 2)
        {
            //T1=NewT;
            unsigned int T1 = triangle.triData.triID;
            unsigned int lT1 = mesh.MaxEdge(T1);
        }

        if (mesh.triMeshData.cell1DMks[lT1] == 5 || mesh.triMeshData.cell1DMks[lT1] == 6 ||
            mesh.triMeshData.cell1DMks[lT1] == 7 || mesh.triMeshData.cell1DMks[lT1] == 8)
        {

            flag=1;
        }
        else
        {

        }
    }
}



}
