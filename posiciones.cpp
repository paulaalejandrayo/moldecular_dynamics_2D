#include "posiciones.hpp"

void actualiza_posiciones (const int N, double *a, double *x, double *v, const float delta)
{
  for (int i=0; i< N; i++)
  {
 
    *(x+i*3)= *(x+i*3)+delta*(*(v+i*3))+delta*delta*(*((a)+i*3))/2;
    *(x+i*3+1)= *(x+i*3+1)+delta*(*(v+i*3+1))+delta*delta*(*((a)+i*3+1))/2;
    *(x+i*3+2)= *(x+i*3+2)+delta*(*(v+i*3+2))+delta*delta*(*((a)+i*3+2))/2;  
    
//     EH=EH+mas_1*g*parts[i][1];
  }
}
