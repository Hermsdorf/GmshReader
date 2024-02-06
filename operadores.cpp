#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include "operadores.h"

using namespace std;
using namespace operadores;


#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}


void operadores::merge (unsigned long vet[], int esq, int meio, int dir )
{
  int i = esq, j = meio + 1, k = 0;
  unsigned long aux[dir - esq + 1];
  while (i <= meio && j <= dir)
    if (vet[i] < vet[j])
      aux[k++] = vet[i++];
    else
      aux[k++] = vet[j++];
  while (i <= meio)
    aux[k++] = vet[i++];
  while (j <= dir)
    aux[k++] = vet[j++];
  for (i = esq; i <= dir; i++)
    vet[i] = aux[i - esq];
}

void operadores::auxMergeSort(unsigned long vet[], int esq, int dir)
{
  if (esq < dir)
  {
    int meio = (esq + dir) / 2;
    auxMergeSort(vet, esq, meio);
    auxMergeSort(vet, meio + 1, dir);
    merge(vet, esq, meio, dir);
  }
}

void operadores::mergeSort(unsigned long vet[], int n)
{
  auxMergeSort(vet, 0, n - 1);
}



unsigned long operadores::EdgeKey(unsigned long a, unsigned long b)
{
    if (a<b)
    {
        swap(a,b);
    }
    unsigned long c = 0;
    mix(a,b,c);
    final(a,b,c);
    return c;
}

unsigned long operadores::TriKey(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long vet[3] = {a,b,c};
    mergeSort(vet,3);
    mix(vet[0],vet[1],vet[2]);
    final(vet[0],vet[1],vet[2]);
    return vet[2];
    /*
    mix(a,b,c);
    final(a,b,c);
    return c;
    */
}

unsigned long operadores::QuadKey(unsigned long a, unsigned long b, 
                                  unsigned long c, unsigned long d)
{
    unsigned long vet[4] = {a,b,c,d};
    
    mergeSort(vet,4);
    mix(vet[0],vet[1],vet[2]);
    vet[0]+=vet[3];
    final(vet[0],vet[1],vet[2]);
    return vet[2];
    /*
    mix(a,b,c);
    a+=d;
    final(a,b,c);
    return c;
    */
}

unsigned long operadores::HexaKey(unsigned long a, unsigned long b,
                                  unsigned long c, unsigned long d,
                                  unsigned long e, unsigned long f,
                                  unsigned long g, unsigned long h)
{
    unsigned long vet[8] = {a,b,c,d,e,f,g,h};
    
    mergeSort(vet,8);
    mix(vet[0],vet[1],vet[2]);
    vet[0]+=vet[3]; vet[1]+=vet[4]; vet[2]+=vet[5];
    mix(vet[0],vet[1],vet[2]);
    vet[0]+=vet[6]; vet[1]+=vet[7];
    final(vet[0],vet[1],vet[2]);
    return vet[2];

    /*
    mix(a,b,c);
    a+=d; b+=e; c+=f;
    mix(a,b,c);
    a+=g; b+=h;
    final(a,b,c);
    return c;
    */
}

unsigned long operadores::CantorKey(unsigned int x, unsigned int y)
{
    if(x>y)
        return (((x+y+1)*(x+y))/2)+x;
    else
        return (((x+y+1)*(x+y))/2)+y;
}
    
unsigned long operadores::ElegantKey(unsigned int x, unsigned int y)
{

    if(x<y)
    {
        return (pow(y,2) + x);
    }
    else
    {   
        return (pow(x,2) + y);
    }

}

GmshNode operadores::EgdeMidpoint(GmshNode p1, GmshNode p2)
{
    GmshNode p3;
    p3.X() = (( p1.X() + p2.X() )/2);
    p3.Y() = (( p1.Y() + p2.Y() )/2); 
    p3.Z() = (( p1.Z() + p2.Z() )/2); 
    return p3;
}

GmshNode operadores::SquareMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4 )
{
    GmshNode cp;
    cp.X() = ( ( p1.X() + p2.X() + p3.X() + p4.X()) / 4 );
    cp.Y() = ( ( p1.Y() + p2.Y() + p3.Y() + p4.Y()) / 4 );
    cp.Z() = ( ( p1.Z() + p2.Z() + p3.Z() + p4.Z()) / 4 );

    return cp;

}

GmshNode operadores::HexaMidpoint(GmshNode p1, GmshNode p2, GmshNode p3, GmshNode p4,
                                  GmshNode p5, GmshNode p6, GmshNode p7, GmshNode p8)
{
    GmshNode cp;
    cp.X() = ( ( p1.X() + p2.X() + p3.X() + p4.X() + p5.X() + p6.X() + p7.X() + p8.X() ) / 8 );
    cp.Y() = ( ( p1.Y() + p2.Y() + p3.Y() + p4.Y() + p5.Y() + p6.Y() + p7.Y() + p8.Y() ) / 8 );
    cp.Z() = ( ( p1.Z() + p2.Z() + p3.Z() + p4.Z() + p5.Z() + p6.Z() + p7.Z() + p8.Z() ) / 8 );

    return cp;
}