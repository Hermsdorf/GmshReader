#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "iomsh.h"

int main()
{
    string line;
    ifstream file("malha.msh");
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        return 0;
    }

    getline(file, line);
    if(line != "$MeshFormat")
    {
        cout << "Invalid file format" << endl;
        return 0;
    }

    Mesh m1;

    file>>m1.FileHeader.Version()>>m1.FileHeader.FileType()>>m1.FileHeader.DataSize();

    cout << m1.FileHeader.Version()<<" "<<m1.FileHeader.FileType()<<" "<<m1.FileHeader.DataSize();
    getline(file, line);//$EndMeshFormat

    getline(file, line);
    if(line != "$PhysicalNames")
    {
        cout << "Invalid file format" << endl;
        return 0;
    }

    file >>m1.NumPhyRegions();
    m1.PhyReg = new GmshPhysicalRegion[m1.NumPhyRegions()];
    getline(file, line);

    for(int i=0; i<m1.NumPhyRegions(); i++)
    {
        file >> m1.PhyReg[i].Dimension()>>m1.PhyReg[i].PhysicalTag()>>m1.PhyReg[i].Name();
        getline(file, line);
        cout << m1.PhyReg[i].Dimension()<<" "<<m1.PhyReg[i].PhysicalTag()<<" "<<m1.PhyReg[i].Name()<<endl;;
    }

    

    return 0;
}