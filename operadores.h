#ifndef OPERADORES_H__
#define OPERADORES_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include "MeshDataStructs.h"

using namespace std;

namespace operadores
{

    unsigned long CantorKey(unsigned int x, unsigned int y);
    unsigned long ElegantKey(unsigned int x, unsigned int y);
    GmshNode EgdeMidpoint(GmshNode p1, GmshNode p2);
    GmshNode SquareMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4 );
    

}
#endif
