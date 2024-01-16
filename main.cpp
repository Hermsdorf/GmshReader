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
    cout << "Selecione o arquivo:"<<endl
         <<"1. malha.msh"<<endl
         <<"2. 3D Surface Cube.msh"<<endl
         <<"3. 3D Volume Cube.msh"<<endl
         <<"4. FullCube.msh"<<endl
         <<"5. malhateste1.msh"<<endl
         <<"6. malhateste2.msh"<<endl
         <<"7. triangle.msh"<<endl;
         
    int fileID = 1;
    cin >> fileID;
    if(fileID == 1)
        file = "Meshes/malha.msh";
    if(fileID == 2)
        file = "Meshes/3D Surface Cube.msh";
    if(fileID == 3)
        file = "Meshes/3D Volume Cube.msh";
    if(fileID == 4)
        file = "Meshes/FullCube.msh";
    if(fileID == 5)
        file = "Meshes/malhateste1.msh";
    if(fileID == 6)
        file = "Meshes/malhateste2.msh";
    if(fileID == 7)
        file = "Meshes/triangle.msh";

    Mesh m;

    cout<<endl;

    cout<< "Carregando Malha...."<<endl;
    m.OpenFile(file);
    cout<< "Armazenando Arestas...."<<endl;
    m.getEdges();
    cout<< "Malha carregada!"<<endl<<endl;


    cout << "----------File Header ----------:"<<endl;
    cout << "File version: "<< m.FileHeader().Version()<<endl;
    cout << "File Type: "<< m.FileHeader().FileType()<<endl;
    cout << "Data size: "<< m.FileHeader().DataSize()<<endl;
    cout<< endl;

    
    cout << "Physical Regions: " << m.NumPhyRegions()<<endl
         << "Nodes: " << m.NumberNodes()<<endl
         << "Elements: " << m.NumberElements()<<endl
         << "Edges: " << m.NumberEdges()<<endl<<endl;

    int ReportDisplay = 2, ExportReport = 1;
    cout <<"Informação detalhada ?"<< endl
         << "1. S" << endl
         << "2. N" << endl;
    cin >> ReportDisplay;

    if (ReportDisplay == 1)
    {
        cout << "Na tela ou Exportar ?" << endl
             << "1. Tela" << endl
             << "2. Exportar" << endl;
        cin >> ExportReport;
    }

    if(ReportDisplay == 1 && ExportReport == 2)
    {
        string filename;
        cout << "Digite o nome do arquivo para exportar: ";
        cin >> filename;
        m.ExportReportFile(filename);
    }

    if(ReportDisplay == 1 && ExportReport == 1)
    {
        cout << "----------Physical Regions ----------:"<<endl<<endl;

    for(int i = 0; i< m.NumPhyRegions(); i++)
    {
        cout<< "Element Tag: "<<m.PhyReg()[i].PhysicalTag()<<endl
            << "Dimension: "<<m.PhyReg()[i].Dimension()<<"  "
            << "Name: "<<m.PhyReg()[i].Name()<<endl<<endl;

    }


        cout << "----------Nodes ----------:"<<endl<<endl;

    for(int i = 0; i< m.NumberNodes(); i++)
    {
        cout<< "Node ID: "<<m.Nodes()[i].ID()<<endl
            << "X = "<<m.Nodes()[i].X()<<"  "
            << "Y = "<<m.Nodes()[i].Y()<<"  "
            << "Z = "<<m.Nodes()[i].Z()<<endl<<endl;

    }

    cout << endl<<endl;

    cout << "---------- Elements ----------:"<<endl<<endl;

    for(int i = 0; i < m.NumberElements(); i++)
    {
        cout << "Element ID: " << m.Elements()[i].ID()<<endl
             << "Element Type: " << m.Elements()[i].Type() << endl
             << "Elements Tags: ";
        for(int j = 0; j < m.Elements()[i].NumTags(); j++)
        {
            cout << m.Elements()[i].Tags()[j]<<" ";
        }
        cout << endl;
        cout << "Element nodes: ";
        for(long unsigned int k = 0; k < m.Elements()[i].Nodes().size(); k++)
        {
            cout << m.Elements()[i].Nodes()[k]<<" ";
        }
        cout << endl;
        cout <<"Element edges: "<< endl;

        if(m.Elements()[i].Type()== 2)
        {
            for(int j = 0; j < 3; j++)
            {
                unsigned long key = CantorKey(m.Elements()[i].Nodes()[m.Tri3Edge[j][0]],m.Elements()[i].Nodes()[m.Tri3Edge[j][1]]);
                cout << "  Edge " << m.EdgeMap[key].id <<": " << m.EdgeMap[key].v1<< " -- " << m.EdgeMap[key].v2 << endl;
            }

        }

        if(m.Elements()[i].Type()== 3)
        {
            for(int j = 0; j < 4; j++)
            {
                unsigned long key = CantorKey(m.Elements()[i].Nodes()[m.Quad4Edge[j][0]],m.Elements()[i].Nodes()[m.Quad4Edge[j][1]]);
                cout << "  Edge " << m.EdgeMap[key].id <<": " << m.EdgeMap[key].v1<< " -- " << m.EdgeMap[key].v2 << endl;
            }

        }

        if(m.Elements()[i].Type()== 4)
        {
            for(int j = 0; j < 6; j++)
            {
                unsigned long key = CantorKey(m.Elements()[i].Nodes()[m.Tetra6Edge[j][0]],m.Elements()[i].Nodes()[m.Tetra6Edge[j][1]]);
                cout << "  Edge " << m.EdgeMap[key].id <<": " << m.EdgeMap[key].v1<< " -- " << m.EdgeMap[key].v2 << endl;
            }

        }

        cout << endl<< endl;

    }

    }

    bool refineMesh = 0;
    cout << "Refinar malha? "<<endl<< "0 - Não  ; 1 - Sim"<<endl;
    cin >> refineMesh;
    if(refineMesh == 1)
    {
        cout<< "Digite o nome da nova malha: ";
        cin >> file;
        file = file + ".msh";
        cout << "Refinando malha...."<<endl;
        m.refine();
        cout << "Amarzenando arestas...."<<endl;
        m.getEdges();
        cout << "Exportando arquivo.msh...."<<endl;
        m.ExportFile(file);
        cout << "Malha "<<file<<" exportada comsucesso!!"<<endl<<endl;
        
    }
    cout << "Programa encerrado."<<endl;
    return 0;
}