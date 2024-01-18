#include "Mesh.h"


Mesh::Mesh(){}
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
    //phyReg = new GmshPhysicalRegion [NumPhyRegions()];
    phyReg.resize(NumPhyRegions());

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
    //nodes = new GmshNode[NumberNodes()];
    nodes.resize(NumberNodes());

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
    //elements = new GmshElement[NumberElements()];
    elements.resize(NumberElements());

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

void Mesh::ExportReportFile(string FileName)
{
    string line;
    ofstream file; 

    file.open(FileName, ios::out);
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }   



    file << "----------File Header ----------:" << '\n';
    file << "File Version: "<< fileHeader.Version() << '\n'
         << "File Type: " << fileHeader.FileType() << '\n'
         << "Data Size: "<< fileHeader.DataSize() << '\n';
    file <<'\n';

    file << "----------Physical Regions ----------:" << '\n';
    for(int i = 0; i< nphyreg; i++)
    {
        file << "Entity Tag: " << phyReg[i].PhysicalTag() << '\n'
             << "Dimension: " << phyReg[i].Dimension() <<'\n'
             << "Name: "<< phyReg[i].Name()<< '\n';
    }
    file <<'\n';

    file << "----------Nodes----------:" << '\n';
    for(int i = 0; i< nnodes; i++)
    {
        file << "Node ID: " << nodes[i].ID() << '\n'
             << "X: " << nodes[i].X() << '\n'
             << "Y: " << nodes[i].Y() <<'\n'
             << "Z: "<< nodes[i].Z()<< '\n';
    }
    file <<'\n';

    file << "----------Elements----------:" << '\n';
    for(int i = 0; i< nelements; i++)
    {
        file << "Element ID: " << elements[i].ID() << '\n'
             << "Element Type: " << elements[i].Type() << '\n'
             << "Element Tags: ";
             for(int j=0; j<elements[i].NumTags();j++)
             {
                file << elements[i].Tags()[j] << " ";
             }file <<'\n';

        file << "Element nodes: ";
        for(long unsigned int k = 0; k < elements[i].Nodes().size(); k++)
        {
            file << elements[i].Nodes()[k]<<" ";
        }file <<'\n';
        
        if(elements[i].Type() >=2)
        {
            
            file << "Element edges: " << '\n';
         if(elements[i].Type()== 2)
        {
            for(int n = 0; n < 3; n++)
            {
                unsigned long key = CantorKey(elements[i].Nodes()[Tri3Edge[n][0]],elements[i].Nodes()[Tri3Edge[n][1]]);
                file << "  Edge " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << '\n';
            }

        }

        if(elements[i].Type()== 3)
        {
            for(int n = 0; n < 4; n++)
            {
                unsigned long key = CantorKey(elements[i].Nodes()[Quad4Edge[n][0]],elements[i].Nodes()[Quad4Edge[n][1]]);
                file << "  Edge " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << '\n';
            }

        }

        if(elements[i].Type()== 4)
        {
            for(int n = 0; n < 6; n++)
            {
                unsigned long key = CantorKey(elements[i].Nodes()[Tetra6Edge[n][0]],elements[i].Nodes()[Tetra6Edge[n][1]]);
                file << "  Edge " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << '\n';
            }

        }
        file <<'\n';

        }
        file <<'\n';
    }
    file <<'\n';
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

int& Mesh::NumberEdges()
{
    return nedges;
}

GmshHeader& Mesh::FileHeader()
{
    return fileHeader;
}

std::vector<GmshPhysicalRegion>& Mesh::PhyReg()
{
    return phyReg;
}

std::vector<GmshNode>& Mesh::Nodes()
{
    return nodes;
}

std::vector<GmshElement>& Mesh::Elements()
{
    return elements;
}

void Mesh::getEdges()
{
    NumberEdges() = 0;
    for(int i=0; i< nelements; i++)
    {
        if(elements[i].Type() == 2)
        {
            //cout << "Element " << elements[i].ID() << endl;
            for(int j=0; j<3; j++)
            {
                int nl1 = Tri3Edge[j][0];
                int nl2 = Tri3Edge[j][1];

                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];

                Edge e(ng1,ng2);
                unsigned long key = CantorKey(e.v1, e.v2);
                if(EdgeMap.find(key) == EdgeMap.end())
                {
                    //
                    e.id = NumberEdges()++;
                    EdgeMap[key] = e;
                }
                //cout << "   Aresta " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << endl;


            }
        }
        if(elements[i].Type() == 3)
        {
            //cout << "Element " << elements[i].ID() << endl;
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
                    e.id =  NumberEdges()++;
                    EdgeMap[key] = e;
                }


                //cout << "   Aresta " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << endl;


            }
            
        }

        if(elements[i].Type() == 4)
            {
                //cout << "Element " << elements[i].ID() << endl;
                for(int j=0; j<6; j++)
                {
                    int nl1 = Tetra6Edge[j][0]; 
                    int nl2 = Tetra6Edge[j][1];
                

                    unsigned int ng1 = elements[i].Nodes()[nl1];
                    unsigned int ng2 = elements[i].Nodes()[nl2];
                    
                    Edge e(ng1,ng2);
                    unsigned long key = CantorKey(e.v1, e.v2);
                    if(EdgeMap.find(key) == EdgeMap.end())
                    {
                        //
                        e.id = NumberEdges()++;
                        EdgeMap[key] = e;
                    }


                    //cout << "   Aresta " << EdgeMap[key].id <<": " << EdgeMap[key].v1<< " -- " << EdgeMap[key].v2 << endl;

                        
                }
            }

        
    }
       
}

void Mesh::NewElement()
{

}

void Mesh::refine()
{

    std::vector<GmshElement> NewElements;
    NewElements.reserve(4*nelements);

    for(int i=0; i<nelements; i++)
    {
        if(this-> elements[i].Type()==1) // Aresta de superfície
        {
            unsigned int ng1 = elements[i].Nodes()[0];
            unsigned int ng2 = elements[i].Nodes()[1];
            unsigned long key = CantorKey(ng1, ng2);
            unsigned long NewVertex[3];
            NewVertex[0] = ng1;
            NewVertex[2] = ng2;
            if(EdgeMap[key].divided == false)
            {
                nnodes++;
                GmshNode node = EgdeMidpoint(nodes[(ng1-1)], nodes[(ng2-1)]);
                EdgeMap[key].divided = true;
                EdgeMap[key].id      = nnodes;
                node.ID()            = nnodes;
                nodes.push_back(node);
                NewVertex[1] = nnodes;
            }
            else
            {
                NewVertex[1] = EdgeMap[key].id;
            }
            for (int k = 0; k < 2; k++)
            {
                GmshElement e;
                e.ID() = NewElements.size()+1;
                e.Type() = elements[i].Type();
                e.NumTags() = elements[i].NumTags();
                e.Tags().resize(e.NumTags());
                for(int n = 0; n < e.NumTags(); n++)
                {
                    e.Tags()[n]=elements[i].Tags()[n];
                }
                e.Nodes().resize(ElementType[e.Type()]);
                e.Nodes()[0]= NewVertex[k];
                e.Nodes()[1]= NewVertex[k+1];
                NewElements.push_back(e);
            }
            

        }

        if(this-> elements[i].Type() == 2) // Triangulo
        {
            unsigned long NewVertex[6];
            for (int j = 0; j < 3; j++)
            {                                               //  i  j
                unsigned int ng1 = elements[i].Nodes()[Tri3Edge[j][0]];
                unsigned int ng2 = elements[i].Nodes()[Tri3Edge[j][1]];
                unsigned long key = CantorKey(ng1, ng2);
                NewVertex[j] = ng1;

                if (EdgeMap[key].divided == false)
                {
                    nnodes ++;
                    GmshNode node = EgdeMidpoint(nodes[(ng1-1)], nodes[(ng2-1)]);
                    EdgeMap[key].divided = true;
                    EdgeMap[key].id      = nnodes;
                    node.ID()            = nnodes;
                    nodes.push_back(node);
                    NewVertex[3 + j] = nnodes;
                }
                else
                {
                    NewVertex[3 + j] = EdgeMap[key].id;
                }                
            }

            for(int k=0; k<4; k++)
            {
                GmshElement e;
                e.ID() = NewElements.size()+1;
                e.Type() = elements[i].Type();
                e.NumTags() = elements[i].NumTags();
                e.Tags().resize(e.NumTags());
                for(int n = 0; n < e.NumTags(); n++)
                {
                    e.Tags()[n]=elements[i].Tags()[n];
                }
                e.Nodes().resize(ElementType[e.Type()]);
                for(int m =0; m<ElementType[e.Type()]; m++)
                {
                    unsigned int idx = RefineTriangle[k][m];
                    e.Nodes()[m]= NewVertex[idx];
                }
                NewElements.push_back(e);
            }

        }

        if(this-> elements[i].Type() == 3) // Quadrado
        {
             unsigned long NewVertex[9];
             int points [4];
             for (int j = 0; j < 4; j++)
            {
                unsigned int ng1 = elements[i].Nodes()[Quad4Edge[j][0]];
                unsigned int ng2 = elements[i].Nodes()[Quad4Edge[j][1]];
                unsigned long key = CantorKey(ng1, ng2);
                NewVertex[j] = ng1;
                points[j] = ng1-1;

                if (EdgeMap[key].divided == false)
                {
                    nnodes++;
                    GmshNode node = EgdeMidpoint(nodes[ng1-1], nodes[ng2-1]);
                    EdgeMap[key].divided = true;
                    EdgeMap[key].id      = nnodes;
                    node.ID()            = nnodes;
                    nodes.push_back(node);
                    NewVertex[4 + j] = nnodes;
                }
                else
                {
                    NewVertex[4 + j] = EdgeMap[key].id;
                }                
            }

            // Criado o ponto central do quadrilátero e adicionando o novo nó ao vetor de nós da malha
            nnodes++;
            GmshNode node = SquareMidpoint(nodes[points[0]],nodes[points[1]],nodes[points[2]],nodes[points[3]]);
            node .ID() = nnodes;
            nodes.push_back(node);
            NewVertex[8] = nnodes;

            for(int k=0; k<4; k++)
            {
                GmshElement e;
                e.ID() = NewElements.size();
                e.Type() = elements[i].Type();
                e.NumTags() = elements[i].NumTags();
                e.Tags().resize(e.NumTags());
                for(int n = 0; n < e.NumTags(); n++)
                {
                    e.Tags()[n]=elements[i].Tags()[n];
                }
                e.Nodes().resize(ElementType[e.Type()]);
                for(int m =0; m<ElementType[e.Type()]; m++)
                {
                    unsigned int idx = RefineSquare[k][m];
                    e.Nodes()[m]= NewVertex[idx];
                }
                NewElements.push_back(e);
            }
            
        }

    }
    
    
    nelements = NewElements.size();
    elements.resize(NewElements.size());
    elements = NewElements;
}