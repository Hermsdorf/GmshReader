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

GmshNode  operadores::midpoint(GmshNode p1, GmshNode p2)
{
    GmshNode p3
    p3.X() = (( p1.X() + p2.X() )/2);
    p3.Y() = (( p1.Y() + p2.Y() )/2); 
    p3.Y() = (( p1.Z() + p2.Z() )/2); 
    return p3;
}