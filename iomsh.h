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

    int& NumberNodes();
    int& NumberElements();
    int& NumPhyRegions();




    private:

    GmshHeader FileHeader;
    GmshPhysicalRegion *PhyReg ; 
    GmshNode *nodes;
    GmshElement *elements;

    int nnodes;
    int nelements;
    int nphyreg;
};