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
    unsigned long EdgeKey(unsigned long a, unsigned long b);
    unsigned long TriKey(unsigned long a, unsigned long b, unsigned long c);
    unsigned long QuadKey(unsigned long a, unsigned long b, unsigned long c,unsigned long d);
    unsigned long HexaKey(unsigned long a, unsigned long b, unsigned long c,unsigned long d,
                          unsigned long e, unsigned long f, unsigned long g, unsigned long h);
    GmshNode EgdeMidpoint(GmshNode p1, GmshNode p2);
    GmshNode SquareMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4 );
    

}
#endif
