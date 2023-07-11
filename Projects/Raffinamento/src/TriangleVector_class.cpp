#include "TriangleVector_class.hpp"

namespace ProjectLibrary
{



//Questo serve ad avere un costruttore standar che restituisce un vettore di Triangle vuoto.
TriangleVector::TriangleVector()
{
    triangles.clear();
}


//Questa funzione genera vettori di Triangle a partire dai dati di un oggetto TriangularMesh.
TriangleVector::TriangleVector(TriangularMesh &triMesh)
{
    //itera attraverso gli identificatori degli elementi 2D
    for(unsigned int triangleID : triMesh.triMeshData.cell2DIDs)
    {
        TriStruct triData(triangleID, triMesh.triMeshData);
        Triangle triangle(triData);
        triangles.push_back(triangle);
    }
}


//Questa funzione viene utilizzato per visualizzare alcuni dati di un vettore contenente triangoli.
void TriangleVector::ShowTriangleVector()
{
    for(Triangle tri : triangles)
        tri.Show();
}


//Questa funzione restituisce la dimensione del vettore di Triangle.
size_t TriangleVector::size() const
{
    return triangles.size();
}


//Questo oeratore restituisce il Triangle i-esimo dal vettore di Triangle.
Triangle& TriangleVector::operator [] (size_t index)
{
    return triangles[index];
}


//L'operatore di confronto == viene utilizzato per confrontare due vettori Triangle e verificare se contengono gli stessi oggetti nello stesso ordine.
bool operator == (TriangleVector obj1, TriangleVector obj2)
{
    if (obj1.size() != obj2.size())
    {
        return false;
    }
    for (size_t i = 0; i < obj1.size(); i++)
    {
        if (obj1[i].triData != obj2[i].triData)
        {
            return false;
        }
    }
    return true;
}


// Restituisce un puntatore al primo elemento del vettore triangles
const Triangle* TriangleVector::begin() const
{
    return &triangles[0];
}


// Restituisce un puntatore all'elemento successivo all'ultimo elemento del vettore triangles
const Triangle* TriangleVector::end() const
{
    return &triangles[0] + triangles.size();
}


//Aggiunge un nuovo triangolo al vettore triangles utilizzando triID e triMeshData
void TriangleVector::Add(unsigned int triID, TriangularMesh& triMesh)
{
    TriStruct triData(triID, triMesh.triMeshData);

    Triangle triangle(triData);

    triangles.push_back(triangle);
}


//Questa funzione seleziona e salva in un oggetto TriangleVector i primi N triangoli di TriangleVector
TriangleVector SelecTriangles(const TriangleVector& triangles, const unsigned int N)
{
    TriangleVector selectedTriangles;
    unsigned int count = 0;

    for (size_t i = 0; i < triangles.size() && count < N; i++)
    {
        selectedTriangles.triangles.push_back(triangles.triangles[i]);
        count++;
    }

    return selectedTriangles;
}


//Funzione per "sistemare" un sottoalbero all'interno di un vettore.
//La funzione scambia i nodi in modo da mantenere la proprietà dell'heap.
void heapify(TriangleVector& triangles, int size, int root)
{
    int largest = root;         //Indice del nodo più grande inizializzato come radice
    int left = 2 * root + 1;    //Indice del figlio sinistro
    int right = 2 * root + 2;   //Indice del figlio destro

    //Confronta il triangolo nel nodo sinistro con il triangolo più grande finora
    while (left < size && triangles[left] < triangles[largest])
    {
        largest = left;
    }

    //Confronta il triangolo nel nodo destro con il triangolo più grande finora
    while (right < size && triangles[right] < triangles[largest])
    {
        largest = right;
    }

    //Se il triangolo più grande non è la radice, scambia i triangoli e richiama heapify sul sottoalbero con radice in 'largest'
    if (largest != root)
    {
        swap(triangles[root], triangles[largest]);
        heapify(triangles, size, largest);
    }
}


//Funzione per ordinare un vettore di triangoli utilizzando l'algoritmo HeapSort.
//La funzione crea un heap estraendo ripetutamente l'elemento radice e ripristinando la proprietà dell'heap.
void HeapSortTriangles(TriangleVector& triangles)
{
    int size = triangles.size();

    //Costruisce un heap dal vettore partendo dal primo nodo interno (size / 2 - 1) fino alla radice.
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(triangles, size, i);

    //Estrae l'elemento radice dall'heap, lo sposta alla fine del vettore e richiama heapify per mantenere la struttura dell'heap.
    for (int i = size - 1; i >= 0; i--)
    {
        swap(triangles[0], triangles[i]);
        heapify(triangles, i, 0);
    }
}



}
