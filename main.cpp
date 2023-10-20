#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "iomsh.h"

int main()
{
    Mesh m;
    m.OpenFile("malha.msh");

    cout << "----------File Header ----------:"<<endl;
    cout << "File version: "<< m.FileHeader().Version()<<endl;
    cout << "File Type: "<< m.FileHeader().FileType()<<endl;
    cout << "Data size: "<< m.FileHeader().DataSize()<<endl;
    cout<< endl<<endl;

    cout << "----------Physical Regions ----------:"<<endl<<endl;

    for(int i = 0; i< m.NumPhyRegions(); i++)
    {
        cout<< "Element Tag: "<<m.PhyReg()[i].PhysicalTag()<<endl
            << "Dimension: "<<m.PhyReg()[i].Dimension()<<"  "
            << "Name: "<<m.PhyReg()[i].Name()<<endl<<endl;

    }

    cout << endl<<endl;
    
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
        cout << endl<< endl;

    }


    return 0;
}