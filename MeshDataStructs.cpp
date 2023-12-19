#include "MeshDataStructs.h"

Edge::Edge(unsigned int vert1, unsigned int vert2)
{
    v1 = vert1;
    v2 = vert2;
    divided=false;
}

Edge::Edge() {}

Edge::~Edge() {}

GmshHeader::GmshHeader(double ver, int ft, int ds)
{

    version = ver;
    this->fileType = ft;
    this->dataSize = ds;
}

GmshHeader::GmshHeader()
{
    version = 0.0;
    this->fileType = 0;
    this->dataSize = 0;
}

GmshHeader::~GmshHeader() {}

double &GmshHeader::Version()
{
    return version;
}

int &GmshHeader::FileType()
{
    return fileType;
}

int &GmshHeader::DataSize()
{
    return dataSize;
}

// GmshPhysicalRegion

GmshPhysicalRegion::GmshPhysicalRegion() {}
GmshPhysicalRegion::~GmshPhysicalRegion() {}

int &GmshPhysicalRegion::Dimension()
{
    return dimension;
}

int &GmshPhysicalRegion::PhysicalTag()
{
    return physicalTag;
}

string &GmshPhysicalRegion::Name()
{
    return name;
}

// GmshNode

GmshNode::GmshNode() {}
GmshNode::~GmshNode() {}

int &GmshNode::ID()
{
    return id;
}

double &GmshNode::X()
{
    return x;
}

double &GmshNode::Y()
{
    return y;
}

double &GmshNode::Z()
{
    return z;
}

// GmshElement

GmshElement::GmshElement() {}
GmshElement::~GmshElement() {}

int &GmshElement::ID()
{
    return id;
}

int &GmshElement::Type()
{
    return type;
}

int &GmshElement::NumTags()
{
    return numTags;
    ;
}

vector<int> &GmshElement::Tags()
{
    return tags;
}

vector<int> &GmshElement::Nodes()
{
    return nodes;
}
