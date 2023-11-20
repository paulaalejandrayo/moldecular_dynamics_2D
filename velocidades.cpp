#include "velocidades.hpp"

void actualiza_velocidades (const int N, double *a, double *v, const float delta)
{
//   double EC=0;
  for (int i=0; i<N; i++)
  {
    *(v+i*3) = *(v+i*3)+0.5*delta* (*(a+i*3));
    *(v+i*3+1) = *(v+i*3+1)+0.5*delta *(*(a+i*3+1));
    *(v+i*3+2) =  *(v+i*3+2)+0.5*delta *(*(a+i*3+2));
//     E=E+mas_1*( vels[i][0]* vels[i][0]+vels[i][1]* vels[i][1])+ 0.5*I1*(vels[i][2]* vels[i][2]);
  }
}