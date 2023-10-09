#include <iostream>
#include <string>

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
    GmshPhysicalRegion::GmshPhysicalRegion();
    GmshPhysicalRegion::~GmshPhysicalRegion();

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
GmshNode::GmshNode();
GmshNode::~GmshNode();

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