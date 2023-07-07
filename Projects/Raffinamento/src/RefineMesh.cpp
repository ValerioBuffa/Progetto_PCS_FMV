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


//Qiesta funzione divide a metà un lato di un triangolo aggiornando i dai della mesh
void TriangularMesh::Bisection(const unsigned int& cell2DID, unsigned int& newcell2DID, const unsigned int& cell1DID,
                               const unsigned int& cell2DID2, unsigned int& newcell2DID2, const unsigned int& cell1DID2,
                               unsigned int& midpoint, const unsigned int& mode)
{
    if (cell1DID >= triMeshData.cell1DIDs.size() && cell2DID >= triMeshData.cell2DIDs.size())
    {
        throw invalid_argument("Invalid input");
    }

    //Salvo i dati dei vetrici del lato
    Vector2i edgeVerts = triMeshData.cell1DVerts[cell1DID];
    unsigned int edgeMk = triMeshData.cell1DMks[cell1DID];

    //Calcolo il punto medio
    Vector2d midPoint = MidPoint(cell1DID);

    // Aggiungere il nuovo punto medio all'elenco dei punti della mesh
    unsigned int newPointID = triMeshData.cell0DIDs.size(); // Nuovo ID del punto
    CreatePoint(newPointID, midPoint, edgeMk);
    midpoint = newPointID;

    //Salvo i dati dei vertici del triangolo
    array<unsigned int, 3>& triangleVerts = triMeshData.cell2DVerts[cell2DID];

    // Trovare l'indice del vertice escluso nell'array dei vertici
    unsigned int excludedVertex = 0;
    for (int i = 0; i < 3; i++)
    {
        if (triangleVerts[i] != static_cast<unsigned int>(edgeVerts[0]) && triangleVerts[i] != static_cast<unsigned int>(edgeVerts[1]))
        {
            excludedVertex = triangleVerts[i];
            break;
        }
    }

    //Cerco gli id dei lati più corti del triangolo
    array<unsigned int, 3> triangleEdge = triMeshData.cell2DEdges[cell2DID];
    array<unsigned int, 2> triEdge;
    int index = 0;
    for (int i = 0; i < 3; i++) {
        if (triangleEdge[i] != cell1DID) {
            triEdge[index] = triangleEdge[i];
            index++;
        }
    }

    //Creo il nuovo lato dato dalla bisezione
    unsigned int newEdgeID = triMeshData.cell1DIDs.size();
    Vector2i newVertsID = {newPointID, excludedVertex};
    CreateEdge(newEdgeID, newVertsID, edgeMk);

    //Aggiorno il lato di input dividendolo con il punto medio
    Vector2i newVertsID1 = {newPointID, edgeVerts[0]};
    UpdateEdge(cell1DID, newVertsID1, edgeMk);

    //Creo l'altro lato di input diviso con il punto medio
    unsigned int newEdgeID2 = triMeshData.cell1DIDs.size();
    Vector2i newVertsID2 = {newPointID, edgeVerts[1]};
    CreateEdge(newEdgeID2, newVertsID2, edgeMk);

    //Preparo gli elementi che servono per aggiornare la mesh per i lati e triangoli
    array<unsigned int, 3> triV1;
    array<unsigned int, 3> triV2;
    array<unsigned int, 3> triE1;
    array<unsigned int, 3> triE2;

    if(triMeshData.cell1DVerts[cell1DID][0] == edgeVerts[0] || triMeshData.cell1DVerts[cell1DID][1] == edgeVerts[0])
    {
        triV1 = {newPointID, excludedVertex, static_cast<unsigned int>(edgeVerts[0])};
        triV2 = {newPointID, excludedVertex, static_cast<unsigned int>(edgeVerts[1])};
    }
    else
    {
        triV1 = {newPointID, excludedVertex, static_cast<unsigned int>(edgeVerts[1])};
        triV2 = {newPointID, excludedVertex, static_cast<unsigned int>(edgeVerts[0])};
    }

    if(triMeshData.cell1DVerts[triEdge[0]][0] == edgeVerts[0] || triMeshData.cell1DVerts[triEdge[1]][0] == edgeVerts[0] ||
       triMeshData.cell1DVerts[triEdge[0]][1] == edgeVerts[0] || triMeshData.cell1DVerts[triEdge[1]][1] == edgeVerts[0])
    {
        triE1= {newEdgeID, cell1DID, triEdge[0]};
        triE2= {newEdgeID, newEdgeID2, triEdge[1]};
    }
    else
    {
        triE1= {newEdgeID, cell1DID, triEdge[1]};
        triE2= {newEdgeID, newEdgeID2, triEdge[0]};
    }

    //Aggiorno il triangolo diviso dal lato
    unsigned int triMK1 = triMeshData.cell2DMks[cell2DID]+1;
    UpdateTriangle(cell2DID, triV1, triE1, triMK1);

    //Creo l'altra metà del triangolo
    newcell2DID = triMeshData.cell2DIDs.size();
    unsigned int triMK2 = triMeshData.cell2DMks[cell2DID] + 1;
    CreateTriangle(newcell2DID, triV2, triE2, triMK2);

    adjacentTriangles[newEdgeID].push_back(cell2DID);
    adjacentTriangles[newEdgeID].push_back(newcell2DID);

    if (mode == 1)
    {
        if (cell1DID2 >= triMeshData.cell1DIDs.size() && cell2DID2 >= triMeshData.cell2DIDs.size())
        {
            throw invalid_argument("Invalid cell1DID2");
        }

        //Salvo i dati dei vetrici del lato del secondo triangolo
        Vector2i edgeVerts2 = triMeshData.cell1DVerts[cell1DID2];

        //Salvo i dati dei vertici del triangolo
        array<unsigned int, 3>& triangleVerts2 = triMeshData.cell2DVerts[cell2DID2];

        // Trovare l'indice del vertice escluso nell'array dei vertici del secondo triangolo
        unsigned int excludedVertex2 = 0;
        for (int i = 0; i < 3; i++)
        {
            if (triangleVerts2[i] != static_cast<unsigned int>(edgeVerts2[0]) && triangleVerts2[i] != static_cast<unsigned int>(edgeVerts2[1]))
            {
                excludedVertex2 = triangleVerts2[i];
                break;
            }
        }

        //Cerco gli id dei lati più corti del secondo triangolo
        array<unsigned int, 3> triangleEdge2 = triMeshData.cell2DEdges[cell2DID];
        array<unsigned int, 2> triEdge2;
        int index = 0;
        for (int i = 0; i < 3; i++) {
            if (triangleEdge2[i] != cell1DID2) {
                triEdge2[index] = triangleEdge2[i];
                index++;
            }
        }

        //Creo il nuovo lato dato dalla bisezione del secondo triangolo
        unsigned int newEdgeID2 = triMeshData.cell1DIDs.size();
        Vector2i newVertsID2 = {newPointID, excludedVertex2};
        CreateEdge(newEdgeID2, newVertsID2, edgeMk);

        //Preparo gli elementi che servono per aggiornare la mesh per i lati e triangoli
        array<unsigned int, 3> triV12;
        array<unsigned int, 3> triV22;
        array<unsigned int, 3> triE12;
        array<unsigned int, 3> triE22;

        if(triMeshData.cell1DVerts[cell1DID2][0] == edgeVerts2[0] || triMeshData.cell1DVerts[cell1DID2][1] == edgeVerts2[0])
        {
            triV12 = {newPointID, excludedVertex2, static_cast<unsigned int>(edgeVerts2[0])};
            triV22 = {newPointID, excludedVertex2, static_cast<unsigned int>(edgeVerts2[1])};
        }
        else
        {
            triV12 = {newPointID, excludedVertex2, static_cast<unsigned int>(edgeVerts2[1])};
            triV22 = {newPointID, excludedVertex2, static_cast<unsigned int>(edgeVerts2[0])};
        }

        if(triMeshData.cell1DVerts[triEdge[0]][0] == edgeVerts2[0] || triMeshData.cell1DVerts[triEdge[1]][0] == edgeVerts2[0] ||
           triMeshData.cell1DVerts[triEdge[0]][1] == edgeVerts2[0] || triMeshData.cell1DVerts[triEdge[1]][1] == edgeVerts2[0])
        {
            triE12= {newEdgeID2, cell1DID2, triEdge[0]};
            triE22= {newEdgeID2, newEdgeID2, triEdge[1]};
        }
        else
        {
            triE12= {newEdgeID2, cell1DID2, triEdge[1]};
            triE22= {newEdgeID2, newEdgeID2, triEdge[0]};
        }

        //Aggiorno il triangolo diviso dal lato
        unsigned int triMK3 = triMeshData.cell2DMks[cell2DID2]+1;
        UpdateTriangle(cell2DID2, triV12, triE12, triMK3);

        //Creo l'altra metà del triangolo
        newcell2DID2 = triMeshData.cell2DIDs.size();
        unsigned int triMK4 = triMeshData.cell2DMks[cell2DID2] + 1;
        CreateTriangle(newcell2DID2, triV22, triE22, triMK4);

        adjacentTriangles[newEdgeID2].push_back(cell2DID2);
        adjacentTriangles[newEdgeID2].push_back(newcell2DID2);

    }
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
    unsigned int T1 = 0;
    unsigned int lT1 = 0;
    unsigned int T2 = 0;
    unsigned int lT2 = 0;
    unsigned int GT1 = 0;
    unsigned int GT2 = 0;
    unsigned int MP = 0;
    unsigned int MP1 = 0;

    while(flag != 1)
    {
        if (flag == 0)
        {
            T1 = triangle.triData.triID;
            lT1 = mesh.MaxEdge(T1);
        }

        if(flag == 2)
        {
            T1=T2;
            lT1 = mesh.MaxEdge(T1);
            cout << T1 << endl;
        }

        if (mesh.triMeshData.cell1DMks[lT1] == 5 || mesh.triMeshData.cell1DMks[lT1] == 6 ||
            mesh.triMeshData.cell1DMks[lT1] == 7 || mesh.triMeshData.cell1DMks[lT1] == 8)
        {
            MP1=MP;

            mesh.Bisection(T1, GT1, lT1, T2, GT2, lT2, MP, 0);

            removed.Add(T1, mesh);
            removed.Add(GT1, mesh);

            //if (falg == 2)
                //create(<PMlT>)

            flag=1;            
        }
        else
        {
            removed.Add(T1, mesh);
            vector<unsigned int> adjacentTriangles = mesh.GetAdjacentTriangles(lT1);

            for (unsigned int i = 0; i < adjacentTriangles.size(); i++)
            {
                if (adjacentTriangles[i] != T1)
                {
                    T2 = adjacentTriangles[i];
                    break;
                }
            }
            cout << T1 << endl;
            cout << T2 << endl;
            unsigned int lT2 = mesh.MaxEdge(T2);
            removed.Add(T2, mesh);

            if (lT1 == lT2)
            {
                MP1=MP;

                mesh.Bisection(T1, GT1, lT1, T2, GT2, lT2, MP, 1);

                removed.Add(T1, mesh);
                removed.Add(GT1, mesh);
                removed.Add(T2, mesh);
                removed.Add(GT2, mesh);

                //if (falg == 2)
                    //create(<PMlT>)

                flag=1;
            }
            else
            {
                MP1=MP;

                mesh.Bisection(T1, GT1, lT1, T2, GT2, lT2, MP, 0);

                removed.Add(T1, mesh);
                removed.Add(GT1, mesh);

                //if (falg == 2)
                    //create(<PMlT>)

                flag=2;
            }
        }
    }
}



}
