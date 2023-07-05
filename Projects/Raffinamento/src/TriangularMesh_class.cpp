#include "TriangularMesh_class.hpp"
#include <fstream>

namespace ProjectLibrary
{



//L'operatore di confronto == viene utilizzato per confrontare due istanze di TriMeshStruct e verificare se contengono gli stessi dati della mesh triangolare.
bool operator == (const TriMeshStruct &obj1, const TriMeshStruct &obj2)
{
    return obj1.cell0DIDs == obj2.cell0DIDs &&
           obj1.cell0DCoords == obj2.cell0DCoords &&
           obj1.cell0DMks == obj2.cell0DMks &&
           obj1.cell1DIDs == obj2.cell1DIDs &&
           obj1.cell1DVerts == obj2.cell1DVerts &&
           obj1.cell1DMks == obj2.cell1DMks &&
           obj1.cell2DIDs == obj2.cell2DIDs &&
           obj1.cell2DVerts == obj2.cell2DVerts &&
           obj1.cell2DEdges == obj2.cell2DEdges;
}


//Costruttore della classe "TriangularMesh". Il costruttore prende tre argomenti di tipo "string" che
//rappresentano i percorsi dei file 0D, 1D e 2D utilizzati per riempire la struttura dei dati della mesh triangolare.
//Il costruttore inizializza un oggetto "TriangularMesh" riempiendo la sua struttura dei dati utilizzando
//i file specificati. La funzione "fillTriMeshStruct" si occupa dell'effettivo caricamento dei dati dai file nella struttura della mesh triangolare.
TriangularMesh::TriangularMesh(const string &filePath0D, const string &filePath1D, const string &filePath2D)
{
    try
    {
        fillTriMeshStruct(triMeshData, adjacentTriangles, filePath0D, filePath1D, filePath2D);
    }
    catch (const exception &e)
    {
        throw;
        //Il blocco "try" è seguito da un blocco "catch" che cattura eventuali eccezioni generate
        //durante l'esecuzione del codice all'interno del blocco "try". In caso di eccezione,
        //viene lanciata nuovamente l'eccezione per essere gestita al di fuori del costruttore.
    }
}


//La funzione "fillTriMeshStruct" è utilizzata per popolare un oggetto "TriMeshStruct" con i dati estratti
//da tre file di input corrispondenti alla geometria di una mesh triangolare.La funzione prende in input
//un oggetto TriMeshStruct chiamato triMeshData, insieme a tre percorsi di file filePath0D, filePath1D e filePath2D.
void fillTriMeshStruct(TriMeshStruct &triMeshData, unordered_map<unsigned int, vector<unsigned int>> &adjacentTriangles, const string &filePath0D, const string &filePath1D, const string &filePath2D)
{
    try
    {
        //Viene aperto il file filePath0D utilizzando std::ifstream e viene verificato se è stato
        //aperto correttamente. Se non è possibile aprire il file, viene lanciata un'eccezione con un messaggio di errore corrispondente.
        ifstream file;
        file.open(filePath0D);
        if (!file.is_open())
            throw runtime_error("Failed to open file at path: " + filePath0D);

        //Vengono dichiarate una stringa line e un vettore di stringhe fileLines per contenere le linee del file.
        string line;
        vector<string> fileLines;

        getline(file, line);//Viene letta la prima riga del file senza fare nulla.

        while (getline(file, line))//vengono lette righe successive.
            fileLines.push_back(line);

        file.close();//chiusura file.

        //Viene effettuato un controllo per verificare se il file contiene dati.
        //Se il vettore fileLines è vuoto, viene lanciata un'eccezione indicando che il file è vuoto.
        if (fileLines.size() == 0)
            throw runtime_error("Failed to extract data from file at path " + filePath0D + ": file is empty");

        //Vengono riservati spazi di memoria per i vettori cell0DIDs e cell0DCoords di triMeshData
        //utilizzando la dimensione di fileLines.
        triMeshData.cell0DIDs.reserve(fileLines.size());
        triMeshData.cell0DCoords.reserve(fileLines.size());
        triMeshData.cell0DMks.reserve(fileLines.size());

        for (const string &line : fileLines) //Viene iterato su ogni riga di fileLines.
        {
            //Ogni riga viene suddivisa utilizzando istringstream per estrarre l'ID, il marcatore e le coordinate del vertice.
            istringstream iss(line);
            unsigned int id;
            unsigned int marker;
            Vector2d coords;

            iss >> id >> marker >> coords(0) >> coords(1);

            //L'ID viene inserito in cell0DIDs, le coordinate vengono inserite in cell0DCoords.
            triMeshData.cell0DIDs.push_back(id);
            triMeshData.cell0DMks.push_back(marker);
            triMeshData.cell0DCoords.push_back(coords);
        }

        fileLines.clear();//Il vettore fileLines viene svuotato.



        //Il processo viene ripetuto per filePath1D e filePath2D, leggendo rispettivamente le righe per
        //gli spigoli 1D e i triangoli 2D, e popolando i vettori corrispondenti di triMeshData.
        file.open(filePath1D);

        if (!file.is_open())
            throw runtime_error("Failed to open file at path: " + filePath1D);

        getline(file, line);

        while (getline(file, line))
            fileLines.push_back(line);

        file.close();

        if (fileLines.size() == 0)
            throw runtime_error("Failed to extract data from file at path " + filePath1D + ": file is empty");

        triMeshData.cell1DIDs.reserve(fileLines.size());
        triMeshData.cell1DVerts.reserve(fileLines.size());
        triMeshData.cell1DMks.reserve(fileLines.size());

        for (const string &line : fileLines)
        {
            istringstream iss(line);
            unsigned int id;
            unsigned int marker;
            Vector2i verts;

            iss >> id >> marker >> verts(0) >> verts(1);

            triMeshData.cell1DIDs.push_back(id);
            triMeshData.cell1DVerts.push_back(verts);
            triMeshData.cell1DMks.push_back(marker);
        }

        fileLines.clear();// fine secondo pezzo



        file.open(filePath2D);//inizio terzo pezzo

        if (!file.is_open())
            throw runtime_error("Failed to open file at path: " + filePath2D);

        getline(file, line);

        while (getline(file, line))
            fileLines.push_back(line);

        file.close();

        if (fileLines.size() == 0)
            throw runtime_error("Failed to extract data from file at path " + filePath2D + ": file is empty");

        unsigned int count = 1;
        for (char c : fileLines[1])
        {
            if (c == ' ')
            {
                count++;
            }
        }

        triMeshData.cell2DIDs.reserve(fileLines.size());
        triMeshData.cell2DVerts.reserve(fileLines.size());
        triMeshData.cell2DEdges.reserve(fileLines.size());
        triMeshData.cell2DMks.reserve(fileLines.size());

        for (const string &line : fileLines)
        {
            istringstream iss(line);
            unsigned int id;
            unsigned int marker;
            array<unsigned int, 3> verts;
            array<unsigned int, 3> edges;

            iss >> id;
            if(count == 7)
            {
                marker=0;
                for (unsigned int i = 0; i < 3; i++)
                    iss >> verts[i];
                for (unsigned int i = 0; i < 3; i++)
                {
                    iss >> edges[i];
                    adjacentTriangles[edges[i]].push_back(id);
                }

                triMeshData.cell2DIDs.push_back(id);
                triMeshData.cell2DVerts.push_back(verts);
                triMeshData.cell2DEdges.push_back(edges);
                triMeshData.cell2DMks.push_back(marker);


            }
            else if(count == 8)
            {
                iss >> marker;
                for (unsigned int i = 0; i < 3; i++)
                    iss >> verts[i];
                for (unsigned int i = 0; i < 3; i++)
                {
                    iss >> edges[i];
                    adjacentTriangles[edges[i]].push_back(id);
                }

                triMeshData.cell2DIDs.push_back(id);
                triMeshData.cell2DVerts.push_back(verts);
                triMeshData.cell2DEdges.push_back(edges);
                triMeshData.cell2DMks.push_back(marker);
            }
        }

    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        throw;
    }
}


//Questa funzione viene utilizzato per visualizzare tutte i dat sulla mesh triangolare.
void TriangularMesh::Show()
{
    cout << "Cell0D:" << endl;
    for (const unsigned int &id : triMeshData.cell0DIDs)
    {
        cout << "ID: " << id;
        cout << "   \tMarker: " << triMeshData.cell0DMks[id];
        cout << "   \tX: " << triMeshData.cell0DCoords[id][0];
        cout << "   \tY: " << triMeshData.cell0DCoords[id][1];
        cout << endl;
    }


    cout << "Cell1D:" << endl;
    for (const unsigned int &id : triMeshData.cell1DIDs)
    {
        cout << "ID: " << id;
        cout << "   \tMarker: " << triMeshData.cell1DMks[id];
        cout << "   \tOrigin: " << triMeshData.cell1DVerts[id][0];
        cout << "   \tEnd: " << triMeshData.cell1DVerts[id][1];
        cout << endl;
    }



    cout << "Cell2D:" << endl;
    for (const unsigned int &id : triMeshData.cell2DIDs)
    {
        cout << "ID: " << id;
        cout << "   \tMarker: " << triMeshData.cell2DMks[id];
        cout << "   \tVertices: ";
        for (unsigned int i = 0; i < 3; i++)
            cout << "     " << triMeshData.cell2DVerts[id][i];
        cout << "   \tEdges: ";
        for (unsigned int i = 0; i < 3; i++)
            cout << "   " << triMeshData.cell2DEdges[id][i];
        cout << endl;
    }
}


//Questa funzione restituisce il vettore di Id dei Triangle adiacenti ad un lato.
vector<unsigned int> TriangularMesh::GetAdjacentTriangles(unsigned int edgeId)
{
    return adjacentTriangles[edgeId];
}


void PrintToCSV0(const string& filePathOut0, TriMeshStruct &triMeshData)
{
    try
    {
        ofstream file(filePathOut0, ofstream::trunc);
        if (!file.is_open())
            throw runtime_error("Failed to open file: " + filePathOut0);

        file << "Id Marker X Y" << "\n";
        for(const unsigned int &id : triMeshData.cell0DIDs)
        {
            file << id << " "
                 << triMeshData.cell0DMks[id] << " "
                 << triMeshData.cell0DCoords[id][0] << " "
                 << triMeshData.cell0DCoords[id][1] << "\n";
        }

        file.close();
    }
    catch (const std::exception& e)
    {
        cerr << "Error writing to CSV file: " << e.what() << endl;
        throw;
   }
}


void PrintToCSV1(const string& filePathOut1, TriMeshStruct &triMeshData)
{
    try
    {
        ofstream file(filePathOut1, ofstream::trunc);
        if (!file.is_open())
            throw runtime_error("Failed to open file: " + filePathOut1);

        file << "Id Marker Origin End" << "\n";
        for(const unsigned int &id : triMeshData.cell1DIDs)
        {
            file << id << " "
                 << triMeshData.cell1DMks[id] << " "
                 << triMeshData.cell1DVerts[id][0] << " "
                 << triMeshData.cell1DVerts[id][1] << "\n";
        }

        file.close();
    }
    catch (const std::exception& e)
    {
        cerr << "Error writing to CSV file: " << e.what() << endl;
        throw;
   }
}


void PrintToCSV2(const string& filePathOut2, TriMeshStruct &triMeshData)
{
    try
    {
        ofstream file(filePathOut2, ofstream::trunc);
        if (!file.is_open())
            throw runtime_error("Failed to open file: " + filePathOut2);

        file << "Id Marker Vertices Edges" << "\n";
        for(const unsigned int &id : triMeshData.cell2DIDs)
        {
            file << id << " "
                 << triMeshData.cell2DMks[id];
            for(unsigned int i = 0; i < 3; i++)
            {
                file << " " << triMeshData.cell2DVerts[id][i] ;
            }
            for(unsigned int i = 0; i < 3; i++)
            {
                file << " " << triMeshData.cell2DEdges[id][i];
            }
            file << "\n";
        }

        file.close();
    }
    catch (const std::exception& e)
    {
        cerr << "Error writing to CSV file: " << e.what() << endl;
        throw;
   }
}


void TriangularMesh::PrintToCSV(const string& filePath0, const string& filePath1, const string& filePath2)
{
    PrintToCSV0(filePath0, triMeshData);
    PrintToCSV1(filePath1, triMeshData);
    PrintToCSV2(filePath2, triMeshData);
}



}
