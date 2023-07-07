#include "TriangularMesh_class.hpp"
#include "Triangle_class.hpp"
#include "TriangleVector_class.hpp"

using namespace ProjectLibrary;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5)
            throw runtime_error("Fatal failure: check the arguments");

        TriangularMesh mesh(argv[1], argv[2], argv[3]);
        //mesh.Show();

        double n = stod(argv[4]);

        int N = ToRefine(mesh, n);
        cout << N << " Triangle to refine" << endl;

        Refine(mesh, N);

        //mesh.Show();

        mesh.PrintToCSV("D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell0Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell1Ds.csv",
                        "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell2Ds.csv");
    }
    catch (const exception& e)
    {
        cout << "Exception occurred: " << e.what() << endl;
        return -1;
    }
}
