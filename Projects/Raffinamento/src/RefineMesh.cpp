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


//Questa funzione divide a metà un lato di un triangolo aggiornando i dai della mesh
void TriangularMesh::Bisection(const unsigned int& T1, unsigned int& GT1, const unsigned int& lT1,
                               const unsigned int& T2, unsigned int& GT2,
                               unsigned int& MP1, const unsigned int& MP2,
                               const unsigned int& flag, const unsigned int& mode)
{
    if (T1 >= triMeshData.cell2DIDs.size())
    {
        throw invalid_argument("Invalid T1");
    }

    if (lT1 >= triMeshData.cell1DIDs.size())
    {
        throw invalid_argument("Invalid lT1");
    }

    // Salvo i dati dei vetrici del lato
    Vector2i lT1VertOld = triMeshData.cell1DVerts[lT1];
    unsigned int lT1Mk = triMeshData.cell1DMks[lT1];

    // Calcolo il punto medio
    Vector2d midPoint = MidPoint(lT1);

    // Aggiungo il nuovo punto medio all'elenco dei punti della mesh
    MP1 = triMeshData.cell0DIDs.size(); // Nuovo ID del punto
    CreatePoint(MP1, midPoint, lT1Mk);

    // Salvo i dati dei vertici del triangolo
    array<unsigned int, 3>& T1VertOld = triMeshData.cell2DVerts[T1];

    // Trovo l'indice del vertice escluso nell'array dei vertici
    unsigned int PlT1opp = 0;
    for (int i = 0; i < 3; i++)
    {
        if (T1VertOld[i] != static_cast<unsigned int>(lT1VertOld[0]) && T1VertOld[i] != static_cast<unsigned int>(lT1VertOld[1]))
        {
            PlT1opp = T1VertOld[i];
            break;
        }
    }

    // Cerco gli id dei lati più corti del triangolo
    array<unsigned int, 3> T1EdgeOld = triMeshData.cell2DEdges[T1];
    array<unsigned int, 2> T1OtherEdge;
    int index = 0;
    for (int i = 0; i < 3; i++) {
        if (T1EdgeOld[i] != lT1) {
            T1OtherEdge[index] = T1EdgeOld[i];
            index++;
        }
    }

    // Creo il nuovo lato dato dalla bisezione
    unsigned int lMP1 = triMeshData.cell1DIDs.size();
    Vector2i MP1Vert = {MP1, PlT1opp};
    CreateEdge(lMP1, MP1Vert, 0);

    // Aggiorno il lato di input dividendolo con il punto medio
    Vector2i LT1Vert = {MP1, lT1VertOld[0]};
    UpdateEdge(lT1, LT1Vert, lT1Mk);

    // Creo l'altro lato di input diviso con il punto medio
    unsigned int dlT1 = triMeshData.cell1DIDs.size();
    Vector2i dlT1newVert = {MP1, lT1VertOld[1]};
    CreateEdge(dlT1, dlT1newVert, lT1Mk);

    // Preparo gli elementi che servono per aggiornare la mesh per i lati e triangoli
    array<unsigned int, 3> T1Vert;
    array<unsigned int, 3> GT1Vert;
    array<unsigned int, 3> T1Edge;
    array<unsigned int, 3> GT1Edge;

    if (triMeshData.cell1DVerts[lT1][0] == lT1VertOld[0] || triMeshData.cell1DVerts[lT1][1] == lT1VertOld[0])
    {
        T1Vert = {MP1, PlT1opp, static_cast<unsigned int>(lT1VertOld[0])};
        GT1Vert = {MP1, PlT1opp, static_cast<unsigned int>(lT1VertOld[1])};
    }
    else
    {
        T1Vert = {MP1, PlT1opp, static_cast<unsigned int>(lT1VertOld[1])};
        GT1Vert = {MP1, PlT1opp, static_cast<unsigned int>(lT1VertOld[0])};
    }

    if (triMeshData.cell1DVerts[T1OtherEdge[0]][0] == lT1VertOld[0] || triMeshData.cell1DVerts[T1OtherEdge[0]][1] == lT1VertOld[0])
    {
        T1Edge = {lMP1, lT1, T1OtherEdge[0]};
        GT1Edge = {lMP1, dlT1, T1OtherEdge[1]};
    }
    else
    {
        T1Edge = {lMP1, lT1, T1OtherEdge[1]};
        GT1Edge = {lMP1, dlT1, T1OtherEdge[0]};
    }

    // Aggiorno il triangolo diviso dal lato
    unsigned int T1Mk0 = triMeshData.cell2DMks[T1];
    unsigned int T1Mk = T1Mk0 + 1;
    UpdateTriangle(T1, T1Vert, T1Edge, T1Mk);

    // Creo l'altra metà del triangolo
    GT1 = triMeshData.cell2DIDs.size();
    unsigned int GT1Mk = T1Mk0 + 1;
    CreateTriangle(GT1, GT1Vert, GT1Edge, GT1Mk);

    adjacentTriangles[lMP1].push_back(T1);
    adjacentTriangles[lMP1].push_back(GT1);
    adjacentTriangles[dlT1].push_back(GT1);

    adjacentTriangles[GT1Edge[2]].erase(
        remove( adjacentTriangles[GT1Edge[2]].begin(), adjacentTriangles[GT1Edge[2]].end(), T1 ),
        adjacentTriangles[GT1Edge[2]].end() );
    adjacentTriangles[GT1Edge[2]].push_back(GT1);


    //Si attiva questa modalità nel caso lT1==lT2
    if (mode == 1)
    {
        if (T2 >= triMeshData.cell2DIDs.size())
        {
            throw invalid_argument("Invalid T2");
        }

        // Salvo i dati dei vertici del triangolo
        array<unsigned int, 3>& T2VertOld = triMeshData.cell2DVerts[T2];

        // Trovo l'indice del vertice escluso nell'array dei vertici del secondo triangolo
        unsigned int PlT2opp = 0;
        for (int i = 0; i < 3; i++)
        {
            if (T2VertOld[i] != static_cast<unsigned int>(lT1VertOld[0]) && T2VertOld[i] != static_cast<unsigned int>(lT1VertOld[1]))
            {
                PlT2opp = T2VertOld[i];
                break;
            }
        }

        // Cerco gli id dei lati più corti del secondo triangolo
        array<unsigned int, 3> T2EdgeOld = triMeshData.cell2DEdges[T2];
        array<unsigned int, 2> T2OtherEdge;
        index = 0;
        for (int i = 0; i < 3; i++) {
            if (T2EdgeOld[i] != lT1) {
                T2OtherEdge[index] = T2EdgeOld[i];
                index++;
            }
        }

        // Creo il nuovo lato dato dalla bisezione del secondo triangolo
        unsigned int lMP2 = triMeshData.cell1DIDs.size();
        Vector2i lT2Vert = {MP1, PlT2opp};
        CreateEdge(lMP2, lT2Vert, 0);

        // Preparo gli elementi che servono per aggiornare la mesh per i lati e triangoli
        array<unsigned int, 3> T2Vert;
        array<unsigned int, 3> GT2Vert;
        array<unsigned int, 3> T2Edge;
        array<unsigned int, 3> GT2Edge;

        if (triMeshData.cell1DVerts[lT1][0] == lT1VertOld[0] || triMeshData.cell1DVerts[lT1][1] == lT1VertOld[0])
        {
            T2Vert = {MP1, PlT2opp, static_cast<unsigned int>(lT1VertOld[0])};
            GT2Vert = {MP1, PlT2opp, static_cast<unsigned int>(lT1VertOld[1])};
        }
        else
        {
            T2Vert = {MP1, PlT2opp, static_cast<unsigned int>(lT1VertOld[1])};
            GT2Vert = {MP1, PlT2opp, static_cast<unsigned int>(lT1VertOld[0])};
        }

        if (triMeshData.cell1DVerts[T2OtherEdge[0]][0] == lT1VertOld[0] || triMeshData.cell1DVerts[T2OtherEdge[0]][1] == lT1VertOld[0])
        {
            T2Edge = {lMP2, lT1, T2OtherEdge[0]};
            GT2Edge = {lMP2, dlT1, T2OtherEdge[1]};
        }
        else
        {
            T2Edge = {lMP2, lT1, T2OtherEdge[1]};
            GT2Edge = {lMP2, dlT1, T2OtherEdge[0]};
        }

        // Aggiorno il triangolo diviso dal lato
        unsigned int T2Mk0 = triMeshData.cell2DMks[T2];
        unsigned int T2Mk = T2Mk0 + 1;
        UpdateTriangle(T2, T2Vert, T2Edge, T2Mk);

        // Creo l'altra metà del triangolo
        GT2 = triMeshData.cell2DIDs.size();
        unsigned int GT2Mk = T2Mk0 + 1;
        CreateTriangle(GT2, GT2Vert, GT2Edge, GT2Mk);

        adjacentTriangles[lMP2].push_back(T2);
        adjacentTriangles[lMP2].push_back(GT2);
        adjacentTriangles[dlT1].push_back(GT2);

        adjacentTriangles[GT2Edge[2]].erase(
            remove( adjacentTriangles[GT2Edge[2]].begin(), adjacentTriangles[GT2Edge[2]].end(), T2 ),
            adjacentTriangles[GT2Edge[2]].end() );
        adjacentTriangles[GT2Edge[2]].push_back(GT2);
    }


    //Si attiva solo se c'è da completare il segmento tra due punti medi
    if(flag == 2)
    {
        // Creo il nuovo lato dai due punti medi
        unsigned int lMP = triMeshData.cell1DIDs.size();
        Vector2i MPVert = {MP1, MP2};
        CreateEdge(lMP, MPVert, 0);



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
    unsigned int mode = 0;
    unsigned int T1 = 0;
    unsigned int lT1 = 0;
    unsigned int T2 = 0;
    unsigned int lT2 = 0;
    unsigned int GT1 = 0;
    unsigned int GT2 = 0;
    unsigned int MP1 = 0;
    unsigned int MP2 = 0;

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
        }

        if (mesh.triMeshData.cell1DMks[lT1] == 5 || mesh.triMeshData.cell1DMks[lT1] == 6 ||
            mesh.triMeshData.cell1DMks[lT1] == 7 || mesh.triMeshData.cell1DMks[lT1] == 8)
        {
            MP2=MP1;

            mode = 0;
            mesh.Bisection(T1, GT1, lT1, T2, GT2, MP1, MP2, flag, mode);

            removed.Add(T1, mesh);
            removed.Add(GT1, mesh);

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

            lT2 = mesh.MaxEdge(T2);
            removed.Add(T2, mesh);

            if (lT1 == lT2)
            {
                MP2=MP1;

                mode = 1;
                mesh.Bisection(T1, GT1, lT1, T2, GT2, MP1, MP2, flag, mode);

                removed.Add(T1, mesh);
                removed.Add(GT1, mesh);
                removed.Add(T2, mesh);
                removed.Add(GT2, mesh);

                flag=1;
            }
            else
            {
                MP2=MP1;

                mode = 0;
                mesh.Bisection(T1, GT1, lT1, T2, GT2, MP1, MP2, flag, mode);

                removed.Add(T1, mesh);
                removed.Add(GT1, mesh);

                flag=2;
            }
        }
    }
}



}
