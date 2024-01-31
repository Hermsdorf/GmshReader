#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Mesh.h"
#include "operadores.h"

using namespace operadores;

int main()
{
    string file;
    cout << "Selecione o arquivo:" << endl
         << "1. malha.msh" << endl
         << "2. 3D Surface Cube.msh" << endl
         << "3. 3D Volume Cube.msh" << endl
         << "4. FullCube.msh" << endl
         << "5. malhateste1.msh" << endl
         << "6. malhateste2.msh" << endl
         << "7. triangle.msh" << endl
         << "8. testeref.msh" << endl;

    int fileID = 1;
    cin >> fileID;
    if (fileID == 1)
        file = "Meshes/malha.msh";
    if (fileID == 2)
        file = "Meshes/3D Surface Cube.msh";
    if (fileID == 3)
        file = "Meshes/3D Volume Cube.msh";
    if (fileID == 4)
        file = "Meshes/FullCube.msh";
    if (fileID == 5)
        file = "Meshes/malhateste1.msh";
    if (fileID == 6)
        file = "Meshes/malhateste2.msh";
    if (fileID == 7)
        file = "Meshes/triangle.msh";
    if (fileID == 8)
        file = "Meshes/testeref.msh";

    Mesh m;

    cout << endl;

    cout << "Carregando Malha...." << endl;
    m.OpenFile(file);
    cout << "Armazenando Arestas...." << endl;
    m.getEdges();
    cout << "Malha carregada!" << endl
         << endl;

    cout << "----------File Header ----------:" << endl;
    cout << "File version: " << m.FileHeader().Version() << endl;
    cout << "File Type: " << m.FileHeader().FileType() << endl;
    cout << "Data size: " << m.FileHeader().DataSize() << endl;
    cout << endl;

    cout << "Physical Regions: " << m.NumPhyRegions() << endl
         << "Nodes: " << m.NumberNodes() << endl
         << "Elements: " << m.NumberElements() << endl
         << "Edges: " << m.NumberEdges() << endl
         << endl;

    int Report = 0;
    int ExportReport = 0;
    cout << "Informação detalhada ?" << endl
         << "1. S" << endl
         << "0. N" << endl;
    cin >> Report;

    if (Report == 1)
    {
        cout << "Na tela ou Exportar ?" << endl
             << "0. Tela" << endl
             << "1. Exportar" << endl;
        cin >> ExportReport;

        if (ExportReport == 1)
        {
            m.ExportReportFile();
        }
    }

    if (Report == 1 && ExportReport == 0)
    {
        m.Report();
    }

    bool refineMesh = 0;
    cout << "Refinar malha? " << endl
         << "0 - Não  ; 1 - Sim" << endl;
    cin >> refineMesh;
    if (refineMesh == 1)
    {
        int bfr = m.NumberElements();
        cout << "Digite o nome da nova malha: ";
        cin >> file;
        file = file + ".msh";
        cout << "Refinando malha...." << endl;
        m.refine();
        cout << "Refinando " << bfr << " elementos em " << m.NumberElements() << " elementos." << endl;
        cout << "Amarzenando arestas...." << endl;
        m.getEdges();
        cout << "Exportando arquivo.msh...." << endl;
        m.ExportFile(file);
        cout << "Malha " << file << " exportada comsucesso!!" << endl
             << endl;
    }
    cout << "Programa encerrado." << endl;
    return 0;
}