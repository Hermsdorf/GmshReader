#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


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

    void OpenFile(string FileName);
    void ExportFile(string FileName);

    int& NumPhyRegions();
    int& NumberNodes();
    int& NumberElements();

    GmshHeader& FileHeader();
    GmshPhysicalRegion* PhyReg();
    GmshNode* Nodes();
    GmshElement* Elements();

    private:

    GmshHeader fileHeader;
    GmshPhysicalRegion *phyReg ; 
    GmshNode *nodes;
    GmshElement *elements;
    
    int ElementType[11] = {0,2,3,4,4,8,6,5,3,6,9};
    int nnodes;
    int nelements;
    int nphyreg;
};