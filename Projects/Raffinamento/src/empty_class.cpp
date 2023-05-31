#include "empty_class.hpp"
#include <fstream>

namespace ProjectLibrary
{
    TriangularMesh::TriangularMesh(const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D)
    {
        try {

            fillTriMeshStruct(triMeshData, filePath0D, filePath1D, filePath2D);

        } catch (const std::exception &e) {
            throw;
        }
    }

    TriStruct::TriStruct(unsigned int &id, TriMeshStruct &triMeshData)
    {
        triID = id;
        vertIDs = triMeshData.cell2DVerts[id];

        triCoords[0] = triMeshData.cell0DCoords[vertIDs[0]];
        triCoords[1] = triMeshData.cell0DCoords[vertIDs[1]];
        triCoords[2] = triMeshData.cell0DCoords[vertIDs[2]];
        edgeIDs = triMeshData.cell2DEdges[id];
    }

    double Triangle::Area()
    {
        return 0.5 * std::abs((triData.triCoords[0](0) * (triData.triCoords[1](1) - triData.triCoords[2](1)))
                + (triData.triCoords[1](0) * (triData.triCoords[2](1) - triData.triCoords[0](1)))
                + (triData.triCoords[2](0) * (triData.triCoords[0](1) - triData.triCoords[1](1))));
    }

    void TriangularMesh::Show()
    {
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

    void fillTriMeshStruct(TriMeshStruct &triMeshData, const std::string &filePath0D, const std::string &filePath1D, const std::string &filePath2D)
    {
        try {
            std::ifstream file;

            file.open(filePath0D);

            if (!file.is_open())
                throw std::runtime_error("Failed to open file at path: " + filePath0D);

            std::string line;
            std::vector<std::string> fileLines;

            std::getline(file, line);

            while (std::getline(file, line))
                fileLines.push_back(line);

            file.close();

            if (fileLines.size() == 0)
                throw std::runtime_error("Failed to extract data from file at path " + filePath0D + ": file is empty");

            triMeshData.cell0DIDs.reserve(fileLines.size());
            triMeshData.cell0DCoords.reserve(fileLines.size());

            for (const std::string &line : fileLines)
            {
                std::istringstream iss(line);
                unsigned int id;
                unsigned int marker;
                Eigen::Vector2d coords;

                iss >> id >> marker >> coords(0) >> coords(1);

                triMeshData.cell0DIDs.push_back(id);
                triMeshData.cell0DCoords.push_back(coords);

                if (marker != 0) {
                    if (triMeshData.cell0DMks.find(marker) == triMeshData.cell0DMks.end())
                        triMeshData.cell0DMks.insert({marker, {id}});
                    else
                        triMeshData.cell0DMks[marker].push_back(id);
                }
            }

            fileLines.clear();

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

            fileLines.clear();

            file.open(filePath2D);

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

                triMeshData.cell2DIDs.push_back(id);
                triMeshData.cell2DVerts.push_back(verts);
                triMeshData.cell2DEdges.push_back(edges);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

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

    bool operator == (const TriStruct &obj1, const TriStruct &obj2)
    {
        return obj1.triID == obj2.triID && obj1.triCoords == obj2.triCoords && obj1.vertIDs == obj2.vertIDs && obj1.edgeIDs == obj2.edgeIDs;
    }

    bool descendingOrder(Triangle &a, Triangle &b) {
        return a.Area() > b.Area();
    }

    void genTris(std::list<Triangle> &triList, TriangularMesh &triMesh)
    {
        for (unsigned int &id : triMesh.triMeshData.cell2DIDs)
        {
            TriStruct triData(id, triMesh.triMeshData);
            Triangle tri(triData);
            triList.push_back(tri);
        }
    }

    void sortTris(std::list<Triangle> &triList)
    {
        triList.sort(descendingOrder);
    }
}
