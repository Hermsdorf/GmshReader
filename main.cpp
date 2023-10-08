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

    GmshHeader h1;

    file>>h1.Version()>>h1.FileType()>>h1.DataSize();

cout << h1.Version()<<" "<<h1.FileType()<<" "<<h1.DataSize()<<endl;

    return 0;
}