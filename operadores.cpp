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

