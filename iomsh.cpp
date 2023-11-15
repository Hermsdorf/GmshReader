#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "iomsh.h"

//retorna o indice do vetor nodes do elemento



static int Tri3Edge[3][2] = { 
                                {0,1},{1,2},{2,0}
                             };


static int Quad4Edge[4][2] = {{0,1},
                              {1,2},
                              {2,3},
                              {3,0}
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

int& GmshNode::ID()
{
    return id;
}

double& GmshNode::X()
{
    return x;
}

double& GmshNode::Y()
{
    return y;
}

double& GmshNode::Z()
{
    return z;
}


//GmshElement

GmshElement::GmshElement(){}
GmshElement::~GmshElement(){}

int& GmshElement::ID()
    {
        return id;
    }

int& GmshElement::Type()
    {
        return type;
    }

int& GmshElement::NumTags()
    {
        return numTags;
        ;
    }

vector<int>& GmshElement::Tags()
{
    return tags;
}

vector<int>& GmshElement::Nodes()
{
    return nodes;
}


//Mesh

Mesh::Mesh()
{}
Mesh::~Mesh(){}

void Mesh::OpenFile(string FileName)
{
    string line;
    ifstream file;
    this->dimension = 0;
    

    file.open(FileName, ios::in);
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }

    getline(file,line); //$MeshFormat
    if(line != "$MeshFormat")
    {
        cout << "Invalid file format" << endl;
        //return 0;
    }

    file >> FileHeader().Version()
         >> FileHeader().FileType()
         >> FileHeader().DataSize();
    getline(file,line);
    getline(file,line); //$EndMeshFormat
    

    getline(file,line); //$PhysicalNames
    file >> NumPhyRegions(); getline(file,line); 
    phyReg = new GmshPhysicalRegion [NumPhyRegions()];

    for(int i = 0; i < NumPhyRegions(); i++)
    {
        file >> phyReg[i].Dimension() 
             >> phyReg[i].PhysicalTag()
             >> phyReg[i].Name();
        getline(file, line);
        this->dimension = std::max(this->dimension,phyReg[i].Dimension());// pega a dimensão da malha
    }
    getline(file,line); // $EndPhysicalNames

    /*---------------Nodes---------------*/

    getline(file,line); // $Nodes
    file >> NumberNodes(); getline(file,line); 
    nodes = new GmshNode[NumberNodes()];

    for(int i=0; i< NumberNodes(); i++)
    {
        file >> nodes[i].ID()
             >> nodes[i].X()
             >> nodes[i].Y()
             >> nodes[i].Z();
        getline(file,line);
    }
    getline(file,line); // $EndNodes;

    /*-----------Elements-----------*/

    getline(file,line); // $Elements;
    file >> NumberElements(); getline(file,line);
    elements = new GmshElement[NumberElements()];

    for(int i=0; i<NumberElements(); i++)
    {
        file >> elements[i].ID()
             >> elements[i].Type()
             >> elements[i].NumTags();
        elements[i].Tags().resize(elements[i].NumTags());
        for(int j=0; j< elements[i].NumTags(); j++)
        {
            file >> elements[i].Tags()[j];
        }

        elements[i].Nodes().resize(ElementType[elements[i].Type()]);
        for(int k=0; k<ElementType[elements[i].Type()]; k++)
        {
            file >> elements[i].Nodes()[k];
        }
        getline(file,line);
    }

    

    file.close();

}

void Mesh::ExportFile(string FileName)
{
    string line;
    ofstream file; 

    file.open(FileName, ios::out);
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }


/*---------------Mesh Format---------------*/

    file << "$MeshFormat" << '\n';
    file << FileHeader().Version() << " "
         << FileHeader().FileType() <<" "
         << FileHeader().DataSize() << '\n'
         << "$EndMeshFormat" << '\n'; 


/*---------------Physical Regions---------------*/
    
    file << "$PhysicalNames" << '\n';
    file << NumPhyRegions() << '\n';

     for(int i = 0; i < NumPhyRegions(); i++)
    {
        file << phyReg[i].Dimension() << " " 
             << phyReg[i].PhysicalTag()<< " "
             << phyReg[i].Name() <<'\n';
    }
    file << "$EndPhysicalNames" << '\n';


/*---------------Nodes---------------*/

    file << "$Nodes" << '\n';
    file << NumberNodes()<<'\n';

    for(int i=0; i< NumberNodes(); i++)
    {
        file << nodes[i].ID() << " "
             << nodes[i].X() << " "
             << nodes[i].Y() << " "
             << nodes[i].Z() << '\n';
    }
    file << "$EndNodes" << '\n';


/*--------------Elements--------------*/

    file << "$Elements" << '\n';
    file << NumberElements() << '\n';

    for(int i=0; i<NumberElements(); i++)
    {
        file << elements[i].ID() << " "
             << elements[i].Type() << " "
             << elements[i].NumTags() << " ";
        elements[i].Tags().resize(elements[i].NumTags());
        for(int j=0; j< elements[i].NumTags(); j++)
        {
            file << elements[i].Tags()[j]<< " ";
        }

        elements[i].Nodes().resize(ElementType[elements[i].Type()]);
        for(int k=0; k<ElementType[elements[i].Type()]; k++)
        {
            file << elements[i].Nodes()[k]<< " ";
        }
        file << '\n';
    }
    file << "$EndElements";
    file.close();
}

int& Mesh::NumberNodes()
{
    return nnodes;
}

int& Mesh::NumberElements()
{
    return nelements;
}

int& Mesh::NumPhyRegions()
{
    return nphyreg;
}

GmshHeader& Mesh::FileHeader()
{
    return fileHeader;
}

GmshPhysicalRegion* Mesh::PhyReg()
{
    return phyReg;
}

GmshNode* Mesh::Nodes()
{
    return nodes;
}

GmshElement* Mesh::Elements()
{
    return elements;
}

void Mesh::getEdges()
{
    unsigned int nedges = 0;
    for(int i=0; i<this->nelements; i++)
    {
        if(this->elements[i].Type() == 2)
        {
            cout << "Element " << elements[i].ID() << endl;
            for(int j=0; j<3; j++)
            {
                int nl1 = Tri3Edge[j][0];
                int nl2 = Tri3Edge[j][1];

                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];

                cout << "   Arestas " << j <<": " << ng1 << " -- " << ng2 << endl;


            }
        }
        if(this->elements[i].Type() == 3)
        {
            cout << "Element " << elements[i].ID() << endl;
            for(int j=0; j<4; j++)
            {
                int nl1 = Quad4Edge[j][0]; 
                int nl2 = Quad4Edge[j][1];
                

                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];
                
                Edge e(ng1,ng2);
                unsigned long key = CantorKey(e.v1, e.v2);
                if(EdgeMap.find(key) == EdgeMap.end())
                {
                    //
                    e.id = nedges++;
                    EdgeMap[key] = e;
                }


                cout << "   Aresta " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << endl;


            }
            
        }

        
    }
        cout << "Quantidade de Arestas: "<< nedges<<endl;
       
}

Edge::Edge(unsigned int vert1, unsigned int vert2)
{
    v1 = vert1;
    v2 = vert2;
}

Edge::Edge(){}

Edge::~Edge(){}