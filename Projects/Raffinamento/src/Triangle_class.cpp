#include "Triangle_class.hpp"
#include "TriangularMesh_class.hpp"
#include <fstream>

namespace ProjectLibrary
{
    //costruttore della classe "TriStruct",  prende in input un numero intero "id" e un oggetto "triMeshData" di tipo "TriMeshStruct".
    TriStruct::TriStruct(unsigned int &id, TriMeshStruct &triMeshData)
    {
        triID = id;//ID del triangolo all'interno della struttura dei dati della mesh.
        vertIDs = triMeshData.cell2DVerts[id];//La struttura dei dati "triMeshData" contiene un vettore chiamato "cell2DVerts" che mappa l'ID del triangolo ai suoi vertici.
    // La variabile "triCoords" è un array di dimensione 3 che viene inizializzato con le coordinate dei vertici ottenute dalla struttura dei dati "triMeshData".
        triCoords[0] = triMeshData.cell0DCoords[vertIDs[0]];
        triCoords[1] = triMeshData.cell0DCoords[vertIDs[1]];
        triCoords[2] = triMeshData.cell0DCoords[vertIDs[2]];
        edgeIDs = triMeshData.cell2DEdges[id];//La struttura dei dati "triMeshData" contiene un vettore chiamato "cell2DEdges" che mappa l'ID del triangolo ai suoi spigoli.
    }

    // calcola l'area del triangolo basandosi sulle coordinate dei suoi vertici.
    //L'area del triangolo viene calcolata utilizzando la formula dell'area del triangolo dato tre punti nel piano cartesiano.
     double Triangle::Area()
    {
        return 0.5 * std::abs((triData.triCoords[0](0) * (triData.triCoords[1](1) - triData.triCoords[2](1)))
                + (triData.triCoords[1](0) * (triData.triCoords[2](1) - triData.triCoords[0](1)))
                + (triData.triCoords[2](0) * (triData.triCoords[0](1) - triData.triCoords[1](1))));
        //La formula calcola l'area come il valore assoluto della somma dei prodotti tra le coordinate x dei vertici e le differenze delle coordinate y dei vertici, moltiplicata per 0.5.
    }

//L'operatore di confronto == viene utilizzato per confrontare due istanze di TriStruct e verificare se contengono gli stessi dati relativi al triangolo.
    bool operator == (const TriStruct &obj1, const TriStruct &obj2)
    {
        return obj1.triID == obj2.triID && obj1.triCoords == obj2.triCoords && obj1.vertIDs == obj2.vertIDs && obj1.edgeIDs == obj2.edgeIDs;
    }

/*La funzione descendingOrder è una funzione di confronto utilizzata per ordinare oggetti Triangle
 in ordine decrescente in base all'area dei triangoli. Questa funzione prende due oggetti Triangle
 come parametri a e b e confronta le loro aree utilizzando il metodo Area() definito nella classe Triangle.*/
    bool descendingOrder(Triangle &a, Triangle &b) {
        return a.Area() > b.Area();
    }

 //La funzione genTris genera oggetti Triangle a partire dai dati di un oggetto TriangularMesh e li aggiunge a una lista triList.
    void genTris(std::list<Triangle> &triList, TriangularMesh &triMesh)
    {
        //itera attraverso gli identificatori degli elementi 2D
        for (unsigned int &id : triMesh.triMeshData.cell2DIDs)
        {
            TriStruct triData(id, triMesh.triMeshData);// crea un oggetto TriStruct
            Triangle tri(triData);//utilizza il costruttore della classe Triangle per creare un oggetto Triangle
            triList.push_back(tri);// aggiunge l'oggetto Triangle appena creato alla lista triList con push_back().
        }
    }

    void sortTris(std::list<Triangle> &triList)
    {
        triList.sort(descendingOrder);
    }
}
