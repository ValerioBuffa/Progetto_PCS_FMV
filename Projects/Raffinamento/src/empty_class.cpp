#include "empty_class.hpp"
#include <fstream>

namespace ProjectLibrary
{
/*costruttore della classe "TriangularMesh". Il costruttore prende tre argomenti di tipo "string" che
 rappresentano i percorsi dei file 0D, 1D e 2D utilizzati per riempire la struttura dei dati della mesh triangolare.
 Il costruttore inizializza un oggetto "TriangularMesh" riempiendo la sua struttura dei dati utilizzando
 i file specificati. La funzione "fillTriMeshStruct" si occupa dell'effettivo caricamento dei dati dai file nella struttura della mesh triangolare.*/
TriangularMesh::TriangularMesh(const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D)
    {
        try {

            fillTriMeshStruct(triMeshData, filePath0D, filePath1D, filePath2D);

        } catch (const std::exception &e) {
            throw;
            /*Il blocco "try" è seguito da un blocco "catch" che cattura eventuali eccezioni generate
              durante l'esecuzione del codice all'interno del blocco "try". In caso di eccezione,
              viene lanciata nuovamente l'eccezione per essere gestita al di fuori del costruttore.*/
        }
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

    void TriangularMesh::Show() //"Show" viene utilizzato per visualizzare le informazioni sulla mesh triangolare.
    {
        /*Il primo ciclo "for" itera attraverso il contenuto della mappa "cell0DMks" all'interno della struttura
          dei dati "triMeshData". La mappa rappresenta i marcatori (markers) per i vertici 0D della mesh.
          Per ogni marcatore, vengono stampati il marcatore stesso e gli ID dei vertici associati ad esso,
          insieme alle loro coordinate x e y.*/
        for (const auto &marker : triMeshData.cell0DMks)
        {
            std::cout << "Marker:\t" << marker.first;

            for (const unsigned int &id : marker.second) {
                std::cout << "\t ID:\t" << id
                          << "\txCoord: " << triMeshData.cell0DCoords[id][0]
                          << "\tyCoord: " << triMeshData.cell0DCoords[id][1]
                          << std::endl << "\t";
            }

            std::cout << std::endl;
        }

        std::cout << "Cell1D:" << std::endl;

       /*Il secondo ciclo "for" itera attraverso il contenuto della mappa "cell1DMks" all'interno della struttura
        dei dati "triMeshData". La mappa rappresenta i marcatori per gli spigoli 1D della mesh.
        Per ogni marcatore, vengono stampati il marcatore stesso e gli ID degli spigoli associati ad esso,
        insieme alle loro coordinate di origine e fine.*/
        for (const auto &marker : triMeshData.cell1DMks)
        {
            std::cout << "Marker:\t" << marker.first;

            for (const unsigned int &id : marker.second) {
                std::cout << "\t ID:\t" << id
                          << "\tOrigin: " << triMeshData.cell1DVerts[id][0]
                          << "\tEnd: " << triMeshData.cell1DVerts[id][1]
                          << std::endl << "\t";
            }

            std::cout << std::endl;
        }

        std::cout << "Cell2D:" << std::endl;
        /* Il terzo ciclo "for" itera attraverso il vettore "cell2DIDs" all'interno della struttura dei dati
         "triMeshData". Il vettore contiene gli ID dei triangoli della mesh. Per ogni triangolo,
          vengono stampati l'ID del triangolo, gli ID dei suoi vertici e gli ID dei suoi spigoli.*/
        for (const unsigned int &id : triMeshData.cell2DIDs)
        {
            std::cout << "ID:\t" << id;
            std::cout << "\tVerts:";

            for (unsigned int i = 0; i < 3; i++)
                std::cout << "\t" << triMeshData.cell2DVerts[id][i];

            std::cout << "\tEdges:";

            for (unsigned int i = 0; i < 3; i++)
                std::cout << "\t" << triMeshData.cell2DEdges[id][i];

            std::cout << std::endl;
        }
    }

    /*La funzione "fillTriMeshStruct" è utilizzata per popolare un oggetto "TriMeshStruct" con i dati estratti
      da tre file di input corrispondenti alla geometria di una mesh triangolare.La funzione prende in input
      un oggetto TriMeshStruct chiamato triMeshData, insieme a tre percorsi di file filePath0D, filePath1D e filePath2D.*/
    void fillTriMeshStruct(TriMeshStruct &triMeshData, const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D)
    {
        try {
        /*Viene aperto il file filePath0D utilizzando std::ifstream e viene verificato se è stato
          aperto correttamente. Se non è possibile aprire il file, viene lanciata un'eccezione con un messaggio di errore corrispondente.*/
           std::ifstream file;

            file.open(filePath0D);

            if (!file.is_open())
                throw std::runtime_error("Failed to open file at path: " + filePath0D);
        //Vengono dichiarate una stringa line e un vettore di stringhe fileLines per contenere le linee del file.
            std::string line;
            std::vector<std::string> fileLines;

            std::getline(file, line);//Viene letta la prima riga del file senza fare nulla.

            while (std::getline(file, line))//vengono lette righe successive.
                fileLines.push_back(line);

            file.close();//chiusura file.

            /*Viene effettuato un controllo per verificare se il file contiene dati.
             Se il vettore fileLines è vuoto, viene lanciata un'eccezione indicando che il file è vuoto.*/
            if (fileLines.size() == 0)
                throw std::runtime_error("Failed to extract data from file at path " + filePath0D + ": file is empty");

            /*Vengono riservati spazi di memoria per i vettori cell0DIDs e cell0DCoords di triMeshData
             utilizzando la dimensione di fileLines.*/
            triMeshData.cell0DIDs.reserve(fileLines.size());
            triMeshData.cell0DCoords.reserve(fileLines.size());

            for (const std::string &line : fileLines) //Viene iterato su ogni riga di fileLines.
            {
                //Ogni riga viene suddivisa utilizzando istringstream per estrarre l'ID, il marcatore e le coordinate del vertice.
                std::istringstream iss(line);
                unsigned int id;
                unsigned int marker;
                Eigen::Vector2d coords;

                iss >> id >> marker >> coords(0) >> coords(1);

                //L'ID viene inserito in cell0DIDs, le coordinate vengono inserite in cell0DCoords.
                triMeshData.cell0DIDs.push_back(id);
                triMeshData.cell0DCoords.push_back(coords);

                /*Se il marcatore non è zero, viene verificato se il marcatore esiste già all'interno di
                  cell0DMks. Se non esiste, viene inserito con il relativo ID nel formato {marker, {id}}.
                  Se esiste già, l'ID viene aggiunto al vettore corrispondente.*/
                if (marker != 0) {
                    if (triMeshData.cell0DMks.find(marker) == triMeshData.cell0DMks.end())
                        triMeshData.cell0DMks.insert({marker, {id}});
                    else
                        triMeshData.cell0DMks[marker].push_back(id);
                }
            }

            fileLines.clear();//Il vettore fileLines viene svuotato.

            /*Il processo viene ripetuto per filePath1D e filePath2D, leggendo rispettivamente le righe per
            gli spigoli 1D e i triangoli 2D, e popolando i vettori corrispondenti di triMeshData.*/
            file.open(filePath1D);

            if (!file.is_open())
                throw std::runtime_error("Failed to open file at path: " + filePath1D);

            std::getline(file, line);

            while (std::getline(file, line))
                fileLines.push_back(line);

            file.close();

            if (fileLines.size() == 0)
                throw std::runtime_error("Failed to extract data from file at path " + filePath1D + ": file is empty");

            triMeshData.cell1DIDs.reserve(fileLines.size());
            triMeshData.cell1DVerts.reserve(fileLines.size());

            for (const std::string &line : fileLines)
            {
                std::istringstream iss(line);
                unsigned int id;
                unsigned int marker;
                Eigen::Vector2i verts;

                iss >> id >> marker >> verts(0) >> verts(1);

                triMeshData.cell1DIDs.push_back(id);
                triMeshData.cell1DVerts.push_back(verts);

                if (marker != 0) {
                    if (triMeshData.cell1DMks.find(marker) == triMeshData.cell1DMks.end())
                        triMeshData.cell1DMks.insert({marker, {id}});
                    else
                        triMeshData.cell1DMks[marker].push_back(id);
                }
            }

            fileLines.clear();// fine secondo pezzo

            file.open(filePath2D);//inizio terzo pezzo

            if (!file.is_open())
                throw std::runtime_error("Failed to open file at path: " + filePath2D);

            std::getline(file, line);

            while (std::getline(file, line))
                fileLines.push_back(line);

            file.close();

            if (fileLines.size() == 0)
                throw std::runtime_error("Failed to extract data from file at path " + filePath2D + ": file is empty");

            triMeshData.cell2DIDs.reserve(fileLines.size());
            triMeshData.cell2DVerts.reserve(fileLines.size());
            triMeshData.cell2DEdges.reserve(fileLines.size());

            for (const std::string &line : fileLines)
            {
                std::istringstream iss(line);
                unsigned int id;
                std::array<unsigned int, 3> verts;
                std::array<unsigned int, 3> edges;

                iss >> id;

                for (unsigned int i = 0; i < 3; i++)
                    iss >> verts[i];

                for (unsigned int i = 0; i < 3; i++)
                    iss >> edges[i];
            // l'oggetto triMeshData viene popolato con i dati estratti dai file di input.
                triMeshData.cell2DIDs.push_back(id);
                triMeshData.cell2DVerts.push_back(verts);
                triMeshData.cell2DEdges.push_back(edges);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

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
