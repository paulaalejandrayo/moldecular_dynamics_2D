#include "posiciones_old.hpp"

void copia_posiciones (const int N, double *x, double *x_old)
{
  for (int i=0; i< N; i++)
  {
 
    *(x_old+i*3)= *(x+i*3);
    *(x_old+i*3+1)= *(x+i*3+1);
    *(x_old+i*3+2)= *(x+i*3+2);  
    
//     EH=EH+mas_1*g*parts[i][1];
  }
}
