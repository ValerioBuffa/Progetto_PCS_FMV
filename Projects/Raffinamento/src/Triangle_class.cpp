#include "Triangle_class.hpp"

namespace ProjectLibrary
{



//L'operatore di confronto == viene utilizzato per confrontare due istanze di TriStruct e verificare se contengono gli stessi dati relativi al triangolo.
bool operator == (const TriStruct &obj1, const TriStruct &obj2)
{
    return obj1.triID == obj2.triID && obj1.triCoords == obj2.triCoords && obj1.vertIDs == obj2.vertIDs && obj1.edgeIDs == obj2.edgeIDs;
}


//L'operatore di confronto != viene utilizzato per confrontare due istanze di TriStruct e verificare se non contengono gli stessi dati relativi al triangolo.
bool operator != (const TriStruct &obj1, const TriStruct &obj2)
{
    return obj1.triID != obj2.triID || obj1.triCoords != obj2.triCoords || obj1.vertIDs != obj2.vertIDs || obj1.edgeIDs != obj2.edgeIDs;
}


//L'operatore di confronto > viene utilizzato per confrontare le due aree di Triangle.
bool operator > (Triangle &obj1, Triangle &obj2)
{
    return obj1.Area() > obj2.Area();
}


//L'operatore di confronto >= viene utilizzato per confrontare le due aree di Triangle.
bool operator >= (Triangle &obj1, Triangle &obj2)
{
    return obj1.Area() >= obj2.Area();
}


//L'operatore di confronto < viene utilizzato per confrontare le due aree di Triangle.
bool operator < (Triangle &obj1, Triangle &obj2)
{
    return obj1.Area() < obj2.Area();
}


//L'operatore di confronto <= viene utilizzato per confrontare le due aree di Triangle.
bool operator <= (Triangle &obj1, Triangle &obj2)
{
    return obj1.Area() <= obj2.Area();
}


//costruttore della classe "TriStruct",  prende in input un numero intero "id" e un oggetto "triMeshData" di tipo "TriMeshStruct".
TriStruct::TriStruct(unsigned int &id, TriMeshStruct &triMeshData)
{
    triID = id;//ID del triangolo all'interno della struttura dei dati della mesh.
    vertIDs = triMeshData.cell2DVerts[id];//La struttura dei dati "triMeshData" contiene un vettore chiamato "cell2DVerts" che mappa l'ID del triangolo ai suoi vertici.
    // La variabile "triCoords" è un array di dimensione 3 che viene inizializzato con le coordinate dei vertici ottenute dalla struttura dei dati "triMeshData".
    triCoords[0] = triMeshData.cell0DCoords[vertIDs[0]];
    triCoords[1] = triMeshData.cell0DCoords[vertIDs[1]];
    triCoords[2] = triMeshData.cell0DCoords[vertIDs[2]];
    edgeIDs = triMeshData.cell2DEdges[id];//La struttura dei dati "triMeshData" contiene un vettore chiamato "cell2DEdges" che mappa l'ID del triangolo ai suoi lati.
}


//Questa funzione viene utilizzato per visualizzare alcuni dati di un triangolo.
void Triangle::Show()
{
    cout << "ID: " << triData.triID;
    cout << "\tVertices: ";
    for (unsigned int i = 0; i < 3; i++)
        cout << "   " << triData.vertIDs[i];
    cout << "\tEdges: ";
    for (unsigned int i = 0; i < 3; i++)
        cout << "   " << triData.edgeIDs[i];
    cout << "   \tArea: " << Area();
    cout << endl;
}


// calcola l'area del triangolo basandosi sulle coordinate dei suoi vertici.
//L'area del triangolo viene calcolata utilizzando la formula dell'area del triangolo dato tre punti nel piano cartesiano.
double Triangle::Area()
{
    return 0.5 * abs((triData.triCoords[0](0) * (triData.triCoords[1](1) - triData.triCoords[2](1)))
                   + (triData.triCoords[1](0) * (triData.triCoords[2](1) - triData.triCoords[0](1)))
                   + (triData.triCoords[2](0) * (triData.triCoords[0](1) - triData.triCoords[1](1))));
    //La formula calcola l'area come il valore assoluto della somma dei prodotti tra le coordinate x dei vertici e le differenze delle coordinate y dei vertici, moltiplicata per 0.5.
}



}
