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

void Mesh::Report()
{
        cout << "----------Physical Regions ----------:" << endl;
    for(int i = 0; i< nphyreg; i++)
    {
        cout << "Entity Tag: " << phyReg[i].PhysicalTag() << endl
             << "Dimension: "  << phyReg[i].Dimension()   << endl
             << "Name: "       << phyReg[i].Name()        << endl
             << endl;
    }
    cout <<endl;

    cout << "----------Nodes----------:" << endl;
    for(int i = 0; i< nnodes; i++)
    {
        cout << "Node ID: " << nodes[i].ID() << endl
             << "X: "       << nodes[i].X()  << " "
             << "Y: "       << nodes[i].Y()  << " "
             << "Z: "       << nodes[i].Z()  << endl
             << endl;
    }
    cout << endl;

    cout << "----------Elements----------:" << endl;
    for (int i = 0; i < nelements; i++)
    {
        cout << "Element ID: "   << elements[i].ID()   << endl
             << "Element Type: " << elements[i].Type() << endl
             << "Element Tags: ";
        for (int j = 0; j < elements[i].NumTags(); j++)
        {
            cout << elements[i].Tags()[j] << " ";
        }
        cout << endl;

        cout << "Element nodes: ";
        for (long unsigned int k = 0; k < elements[i].Nodes().size(); k++)
        {
            cout << elements[i].Nodes()[k] << " ";
        }
        cout << endl;

        cout << "Element edges: " << endl;
        if (elements[i].Type() == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                int ng1 = elements[i].Nodes()[Tri3Edge[j][0]];
                int ng2 = elements[i].Nodes()[Tri3Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);                
                
                cout << "  Edge " << EdgeMap[key].id 
                     << ": "      << EdgeMap[key].v1
                     << " -- "    << EdgeMap[key].v2 
                     << endl;
            }
        }

        if (elements[i].Type() == 3)
        {
            for (int j = 0; j < 4; j++)
            {
                int ng1 = elements[i].Nodes()[Quad4Edge[j][0]];
                int ng2 = elements[i].Nodes()[Quad4Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                cout << "  Edge " << EdgeMap[key].id
                     << ": "      << EdgeMap[key].v1 
                     << " -- "    << EdgeMap[key].v2
                     << endl;
            }
        }

        if (elements[i].Type() == 4)
        {
            for (int j = 0; j < 6; j++)
            {
                int ng1 = elements[i].Nodes()[Tetra6Edge[j][0]];
                int ng2 = elements[i].Nodes()[Tetra6Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                cout << "  Edge " << EdgeMap[key].id 
                     << ": "      << EdgeMap[key].v1 
                     << " -- "    << EdgeMap[key].v2 
                     << endl;
            }
        }
        cout << endl;
    }
}

void Mesh::ExportReportFile()

{
    string FileName;
    string line;
    ofstream file; 

    cout << "Digite o nome do arquivo para exportar: ";
    cin >> FileName;
    FileName = FileName + ".txt";

    file.open(FileName, ios::out);
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }   



    file << "----------File Header ----------:"      << '\n';
    file << "File Version: "<< fileHeader.Version()  << '\n'
         << "File Type: "   << fileHeader.FileType() << '\n'
         << "Data Size: "   << fileHeader.DataSize() << '\n';
    file <<'\n';

    file << "----------Physical Regions ----------:" << '\n';
    for(int i = 0; i< nphyreg; i++)
    {
        file << "Entity Tag: " << phyReg[i].PhysicalTag() << '\n'
             << "Dimension: "  << phyReg[i].Dimension()   << '\n'
             << "Name: "       << phyReg[i].Name()        << '\n';
    }
    file <<'\n';

    file << "----------Nodes----------:" << '\n';
    for(int i = 0; i< nnodes; i++)
    {
        file << "Node ID: " << nodes[i].ID() << '\n'
             << "X: "       << nodes[i].X()  << '\n'
             << "Y: "       << nodes[i].Y()  << '\n'
             << "Z: "       << nodes[i].Z()  << '\n';
    }
    file <<'\n';

    file << "----------Elements----------:" << '\n';
    for(int i = 0; i< nelements; i++)
    {
        file << "Element ID: "   << elements[i].ID()   << '\n'
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
            for(int j = 0; j < 3; j++)
            {
                int ng1 = elements[i].Nodes()[Tri3Edge[j][0]];
                int ng2 = elements[i].Nodes()[Tri3Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                file << "  Edge " << EdgeMap[key].id 
                     <<": "       << EdgeMap[key].v1
                     << " -- "    << EdgeMap[key].v2
                     << '\n';
            }

        }

        if(elements[i].Type()== 3)
        {
            for(int j = 0; j < 4; j++)
            {
                int ng1 = elements[i].Nodes()[Quad4Edge[j][0]];
                int ng2 = elements[i].Nodes()[Quad4Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                file << "  Edge " << EdgeMap[key].id 
                     <<": "       << EdgeMap[key].v1
                     << " -- "    << EdgeMap[key].v2 
                     << '\n';
            }

        }

        if(elements[i].Type()== 4)
        {
            for(int j = 0; j < 6; j++)
            {
                int ng1 = elements[i].Nodes()[Tetra6Edge[j][0]];
                int ng2 = elements[i].Nodes()[Tetra6Edge[j][1]];
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                file << "  Edge " << EdgeMap[key].id
                     <<": "       << EdgeMap[key].v1
                     << " -- "    << EdgeMap[key].v2  
                     << '\n';
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
        if(elements[i].Type() == TRIANGLE)
        {
            for(int j=0; j<3; j++)
            {
                int nl1 = Tri3Edge[j][0];
                int nl2 = Tri3Edge[j][1];

                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];

                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                if(EdgeMap.find(key) == EdgeMap.end())
                {
                    e.id = NumberEdges()++;
                    EdgeMap[key] = e;
                }
            }
        }

        if(elements[i].Type() == QUADRANGLE)
        {
            for(int j=0; j<4; j++)
            {
                int nl1 = Quad4Edge[j][0]; 
                int nl2 = Quad4Edge[j][1];
                

                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];
                
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                if(EdgeMap.find(key) == EdgeMap.end())
                {
                    //
                    e.id =  NumberEdges()++;
                    EdgeMap[key] = e;
                }
            }
            
        }

        if(elements[i].Type() == TETRAHEDRON)
            {
                for(int j=0; j<6; j++)
                {
                    int nl1 = Tetra6Edge[j][0]; 
                    int nl2 = Tetra6Edge[j][1];
                

                    unsigned int ng1 = elements[i].Nodes()[nl1];
                    unsigned int ng2 = elements[i].Nodes()[nl2];
                    
                    Edge e(ng1,ng2);
                    unsigned long key = EdgeKey(e.v1, e.v2);
                    if(EdgeMap.find(key) == EdgeMap.end())
                    {
                        //
                        e.id = NumberEdges()++;
                        EdgeMap[key] = e;
                    }                        
                }
            }
        
        if(elements[i].Type() == HEXAHEDRON)
        {
            for(int j=0; j<12; j++)
            {
                int nl1 = Hexa8Edge[j][0]; 
                int nl2 = Hexa8Edge[j][1];
                
                unsigned int ng1 = elements[i].Nodes()[nl1];
                unsigned int ng2 = elements[i].Nodes()[nl2];
                
                Edge e(ng1,ng2);
                unsigned long key = EdgeKey(e.v1, e.v2);
                if(EdgeMap.find(key) == EdgeMap.end())
                {
                    e.id =  NumberEdges()++;
                    EdgeMap[key] = e;
                }
            }
        }

    }
       
}

void Mesh::refine()
{

    std::vector<GmshElement> NewElements;
    NewElements.reserve(4*nelements);

    for(int i=0; i<nelements; i++)
    {

        if(this-> elements[i].Type() == LINE)        // Aresta de superfície
        {
            unsigned int ng1 = elements[i].Nodes()[0];
            unsigned int ng2 = elements[i].Nodes()[1];
            unsigned long key = EdgeKey(ng1, ng2);
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

        if(this-> elements[i].Type() == TRIANGLE)    // Trianguloc de superfície
        {
            unsigned long NewVertex[6];
            for (int j = 0; j < 3; j++)
            {                                               //  i  j
                unsigned int ng1 = elements[i].Nodes()[Tri3Edge[j][0]];
                unsigned int ng2 = elements[i].Nodes()[Tri3Edge[j][1]];
                unsigned long key = EdgeKey(ng1, ng2);
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

        if(this-> elements[i].Type() == QUADRANGLE)  // Quadrado de superfície
        {
             unsigned long NewVertex[9];
             for (int j = 0; j < 4; j++)
            {
                unsigned long ng1 = elements[i].Nodes()[Quad4Edge[j][0]];
                unsigned long ng2 = elements[i].Nodes()[Quad4Edge[j][1]];
                unsigned long key = EdgeKey(ng1, ng2);
                NewVertex[j] = ng1;

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

            // Criado o ponto central do quadrilátero e adicionando o novo nó ao vetor de nós da malha e
            // armazenando este nó na hash cpQuadrangle.
            unsigned long ng1 = elements[i].Nodes()[0];
            unsigned long ng2 = elements[i].Nodes()[1];
            unsigned long ng3 = elements[i].Nodes()[2];
            unsigned long ng4 = elements[i].Nodes()[3];
            unsigned long key = QuadKey(ng1, ng2, ng3, ng4);
            if(cpQuadrangle.find(key) == cpQuadrangle.end())
            {
                nnodes++;
                GmshNode node = QuadMidpoint(nodes[ng1-1], nodes[ng2-1], nodes[ng3-1], nodes[ng4-1]);
                node .ID() = nnodes;
                nodes.push_back(node);
                NewVertex[8] = nnodes;
                cpQuadrangle[key] = node;
            }
            else
            {
                NewVertex[8] = cpQuadrangle[key].ID();
            }

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

        if(this-> elements[i].Type() == TETRAHEDRON) // Tetraedro
        {
            unsigned long NewVertex[10];
            for (int j = 0; j < 4; j++)
            {
                NewVertex[j]= elements[i].Nodes()[j];
            }

            for(int k = 0; k < 6; k++)
            {
                unsigned int ng1 =  elements[i].Nodes()[Tetra6Edge[k][0]];
                unsigned int ng2 =  elements[i].Nodes()[Tetra6Edge[k][1]];
                unsigned long key = EdgeKey(ng1, ng2);
                if (EdgeMap[key].divided == false)
                {
                    nnodes ++;
                    GmshNode node = EgdeMidpoint(nodes[(ng1-1)], nodes[(ng2-1)]);
                    EdgeMap[key].divided = true;
                    EdgeMap[key].id      = nnodes;
                    node.ID()            = nnodes;
                    nodes.push_back(node);
                    NewVertex[4 + k] = nnodes;
                }
                else
                {
                    NewVertex[4 + k] = EdgeMap[key].id;
                }    
            }

            for(int m = 0; m < 8; m++)
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
                for (int n = 0; n < 4; n++)
                {
                    unsigned int idx = RefineTetrahedron[m][n];
                    e.Nodes()[n]= NewVertex[idx];
                }
                NewElements.push_back(e);
            }
            
        }

        if(this-> elements[i].Type() == HEXAHEDRON)  // Hexaedro
        {
            unsigned long NewVertex[27]; // Vetor para armazenar todos os pontos necessários para criar os 8 novos elementos;

            
            for (int j = 0; j < 8; j++) // Rotina apra armazenar os pontos que definem o hexadro a ser refinado;
            {
                NewVertex[j] = elements[i].Nodes()[j];
            }

            for (int k = 0; k < 12; k++) // Rotina para criar  os pontos médios das arestas que formam o hexaedro;
            {
                unsigned long ng1 = elements[i].Nodes()[Hexa8Edge[k][0]];
                unsigned long ng2 = elements[i].Nodes()[Hexa8Edge[k][1]];
                unsigned long key = EdgeKey(ng1, ng2);

                if (EdgeMap[key].divided == false)
                {
                    nnodes++;
                    GmshNode node = EgdeMidpoint(nodes[(ng1 - 1)], nodes[(ng2 - 1)]);
                    EdgeMap[key].divided = true;
                    EdgeMap[key].id = nnodes;
                    node.ID() = nnodes;
                    nodes.push_back(node);
                    NewVertex[8 + k] = nnodes;
                }
                else
                {
                    NewVertex[8 + k] = EdgeMap[key].id;
                }
            }
            
            for(int k = 0; k < 6; k++) // Rotina para criar os nós centrais das faces do hexaedro;
            {
                unsigned long ng1 = elements[i].Nodes()[HexaedroFacesNodes[k][0]];
                unsigned long ng2 = elements[i].Nodes()[HexaedroFacesNodes[k][1]];
                unsigned long ng3 = elements[i].Nodes()[HexaedroFacesNodes[k][2]];
                unsigned long ng4 = elements[i].Nodes()[HexaedroFacesNodes[k][3]];
                unsigned long key = QuadKey(ng1, ng2, ng3, ng4);
                if (cpQuadrangle.find(key) == cpQuadrangle.end())
                {
                    nnodes++;
                    GmshNode node = QuadMidpoint(nodes[ng1 - 1], nodes[ng2 - 1], nodes[ng3 - 1], nodes[ng4 - 1]);
                    node.ID() = nnodes;
                    nodes.push_back(node);
                    cpQuadrangle[key] = node;
                    NewVertex[20 + k] = nnodes;
                }
                else
                {
                    NewVertex[20 + k] = cpQuadrangle[key].ID();
                }
            }

            //Crinado o ponto central do hexaedro;
             unsigned long key = HexaKey(NewVertex[0], NewVertex[1], NewVertex[2], NewVertex[3],
                                         NewVertex[4], NewVertex[5], NewVertex[6], NewVertex[7]);
            if(cpHexahedron.find(key) == cpHexahedron.end())
            {
                nnodes++;
                GmshNode node = HexaMidpoint(nodes[NewVertex[0] - 1], nodes[NewVertex[1] - 1], nodes[NewVertex[2] - 1], nodes[NewVertex[3] - 1],
                                             nodes[NewVertex[4] - 1], nodes[NewVertex[5] - 1], nodes[NewVertex[6] - 1], nodes[NewVertex[7] - 1]);
                node.ID() = nnodes;
                nodes.push_back(node);
                cpHexahedron[key] = node;
                NewVertex[26] = nnodes;
            }
            else
            {
                NewVertex[26] = cpHexahedron[key].ID();
            }

            for(int m = 0; m < 8; m++) // Rotina para criar os 8 novos elementos;
            {
                GmshElement e;
                e.ID() = NewElements.size() + 1;
                e.Type() = elements[i].Type();
                e.NumTags() = elements[i].NumTags();
                e.Tags().resize(e.NumTags());
                for (int n = 0; n < e.NumTags(); n++)
                {
                    e.Tags()[n] = elements[i].Tags()[n];
                }
                e.Nodes().resize(ElementType[e.Type()]);
                for (int n = 0; n < 8; n++)
                {
                    unsigned int idx = RefineHexahedron[m][n];
                    e.Nodes()[n] = NewVertex[idx];
                }
                NewElements.push_back(e);
            }
        }


    }
    // Substituição do vetor de elementos iniciais pelo vetor 
    // de elementos da malha refinada.
    nelements = NewElements.size();
    elements.resize(NewElements.size());
    elements = NewElements;
}