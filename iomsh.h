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


