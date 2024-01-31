
#ifndef MESH_H__
#define MESH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "MeshDataStructs.h"
#include "operadores.h"

#define LINE 1
#define TRIANGLE 2
#define QUADRANGLE 3
#define TETRAHEDRON 4
#define HEXAHEDRON 5

using namespace std;
using namespace operadores;


class Mesh
{
    public:
    Mesh();
    ~Mesh();
//                      j= 0,1      
    int Tri3Edge[3][2] = {{0,1},  //i = 0
                          {1,2},  //i = 1
                          {2,0}}; //i = 2
    int Quad4Edge [4][2] = {{0,1},{1,2},{2,3},{3,0}};
    int Tetra6Edge[6][2] = {{0,1},{0,3},{1,2},{1,3},{2,0},{2,3}};
    
    int RefineTriangle    [4][3] = {{0,3,5}, {3,4,5},{3,1,4}, {5,4,2}};
    int RefineSquare      [4][4] = {{0,4,8,7}, {4,1,5,8},{8,5,2,6},{7,8,6,3}};
    int RefineTetrahedron [8][4] = {{0,4,6,7}, {4,1,5,9}, {6,5,2,8}, {7,9,8,3}, 
                                    {4,6,7,9}, {4,9,5,6}, {6,7,9,8}, {6,8,9,5}};

    void OpenFile(string FileName);
    void ExportFile(string FileName);
    void Report();
    void ExportReportFile();
    void getEdges();
    void refine();
    int& NumPhyRegions();
    int& NumberNodes();
    int& NumberElements();
    int& NumberEdges();

    GmshHeader& FileHeader();
    std::vector<GmshPhysicalRegion>& PhyReg();
    std::vector<GmshNode>&  Nodes();
    std::vector<GmshElement>&  Elements();
    std::unordered_map<unsigned long int , Edge > EdgeMap;
    std::unordered_map<unsigned long int , GmshNode > cpQuadrangle;
    std::unordered_map<unsigned long int , GmshNode > cpHexahedron;

    private:
    
    GmshHeader fileHeader;
    std::vector<GmshPhysicalRegion> phyReg ; 
    std::vector<GmshNode>           nodes;
    std::vector<GmshElement>        elements;

    
    int ElementType[11] = {0,2,3,4,4,8,6,5,3,6,9};
    int nnodes;
    int nelements;
    int nphyreg;
    int dimension;
    int nedges;
};

#endif
