#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;




class Edge
{
    public:
    Edge(unsigned int vert1, unsigned int vert2);
    Edge();
    ~Edge();
    unsigned int id;
    unsigned int v1, v2;


};

class GmshHeader
{
public:
    GmshHeader();
    GmshHeader(double ver, int ft, int ds);
    GmshHeader(const GmshHeader& other) = delete;
    ~GmshHeader();

    double& Version();
    int&    FileType();
    int &   DataSize();

private:
    double version;
    int fileType;
    int dataSize;
};


class GmshPhysicalRegion
{
public:
    GmshPhysicalRegion();
    ~GmshPhysicalRegion();

    int& Dimension();
    int& PhysicalTag();
    string& Name();

private:
    int dimension;
    int physicalTag;
    string name;
};


class GmshNode
{
public:
GmshNode();
~GmshNode();

int& ID();
double& X();
double& Y();
double& Z();

private:
    int id;
    double x;
    double y;
    double z;
};


class GmshElement
{
public:
    GmshElement();
    ~GmshElement();

    int& ID();
    int& Type();
    int& NumTags();
    vector<int>& Tags();
    vector<int>& Nodes();

private:
    int id;
    int type;
    int numTags;
    vector<int> tags;
    vector<int> nodes;
};

class Mesh
{
    public:
    Mesh();
    ~Mesh();

    int Tri3Edge[3][2] = {{0,1},{1,2},{2,0}};
    int Quad4Edge[4][2] = {{0,1},{1,2},{2,3},{3,0}};
    int Tetra6Edge[6][2] = {{0,1},{0,3},{1,2},{1,3},{2,0},{2,3}};

    void OpenFile(string FileName);
    void ExportFile(string FileName);
    void getEdges();

    int& NumPhyRegions();
    int& NumberNodes();
    int& NumberElements();
    int& NumberEdges();

    GmshHeader& FileHeader();
    GmshPhysicalRegion* PhyReg();
    GmshNode* Nodes();
    GmshElement* Elements();
    std::unordered_map<unsigned long int , Edge > EdgeMap;

    private:
    
    GmshHeader fileHeader;
    GmshPhysicalRegion *phyReg ; 
    GmshNode *nodes;
    GmshElement *elements;

    
    int ElementType[11] = {0,2,3,4,4,8,6,5,3,6,9};
    int nnodes;
    int nelements;
    int nphyreg;
    int dimension;
    int nedges;
};
