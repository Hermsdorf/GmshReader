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
    void merge(unsigned long vet[], int esq, int meio, int dir);
    void auxMergeSort(unsigned long vet[], int esq, int dir);
    void mergeSort(unsigned long vet[], int n);

    unsigned long CantorKey(unsigned int x, unsigned int y);
    unsigned long ElegantKey(unsigned int x, unsigned int y);
    unsigned long EdgeKey(unsigned long a, unsigned long b);
    unsigned long TriKey(unsigned long a, unsigned long b, unsigned long c);
    unsigned long QuadKey(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
    unsigned long HexaKey(unsigned long a, unsigned long b, unsigned long c, unsigned long d,
                          unsigned long e, unsigned long f, unsigned long g, unsigned long h);
    GmshNode EgdeMidpoint(GmshNode p1, GmshNode p2);
    GmshNode SquareMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4);
    GmshNode HexaMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4,
                          GmshNode p5, GmshNode p6, GmshNode p7, GmshNode p8);

}
#endif
