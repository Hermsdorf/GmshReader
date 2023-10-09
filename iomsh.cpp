#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "iomsh.h"

GmshHeader::GmshHeader(double ver, int ft, int ds)
{
    version        = ver;
    this->fileType = ft;
    this->dataSize = ds;
}

GmshHeader::GmshHeader()
{   version        = 0.0;
    this->fileType = 0;
    this->dataSize = 0;
}

GmshHeader::~GmshHeader(){}

double& GmshHeader::Version()
{
    return version;
}

int& GmshHeader::FileType()
{
    return fileType;
}

int& GmshHeader::DataSize()
{
    return dataSize;
}


//GmshPhysicalRegion 

GmshPhysicalRegion::GmshPhysicalRegion(){}
GmshPhysicalRegion::~GmshPhysicalRegion(){}


int& GmshPhysicalRegion::Dimension()
{
    return dimension;
}

int& GmshPhysicalRegion::PhysicalTag()
{
    return physicalTag;
}

string& GmshPhysicalRegion::Name()
{
    return name;
}



// GmshNode

GmshNode::GmshNode(){}
GmshNode::~GmshNode(){}