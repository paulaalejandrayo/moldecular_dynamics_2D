#include "posiciones_old.hpp"

void copia_posiciones (const int N, double *x, double *x_old, double *x_update, double *displacement, int *flag_update)
{
  double distance;
  
  if (*flag_update==1)  
    { 
      cout <<  "  flag_update=1 " << endl;
      for (int i=0; i< N; i++)
      {
        *(x_update+i*3)= *(x+i*3);
        *(x_update+i*3+1)= *(x+i*3+1);
        *(x_update+i*3+2)= *(x+i*3+2); 
      }
      *flag_update=0;
//   cout <<  "  flag_update=0 " << endl;
  }
  
    *displacement=0;
    for (int i=0; i< N; i++)
    {
  
      distance=sqrt((*(x_update+i*3)-*(x+i*3))*(*(x_update+i*3)-*(x+i*3))+(*(x_update+i*3+1)-*(x+i*3+1))*(*(x_update+i*3+1)-*(x+i*3+1))+(*(x_update+i*3+2)-*(x+i*3+2))*(*(x_update+i*3+2)-*(x+i*3+2)));
      *displacement=max(*displacement,distance);
  //     (displacement,);
      
      *(x_old+i*3)= *(x+i*3);
      *(x_old+i*3+1)= *(x+i*3+1);
      *(x_old+i*3+2)= *(x+i*3+2); 
    }
  
  

}

