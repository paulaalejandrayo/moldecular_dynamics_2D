#include "neighbours.hpp"
// #include "aceleracion_walss.hpp"
void neighbours (const int N, const float rad1, double *x, int *neigh)
{
  double xdif[2], modxdif, seda;
  int k ;
  
    for (int i=0; i<N; i++)       //clean the vector 
  {
    for (int j=0; j<30 ; j++) 
    {
      *(neigh+i*30+j)=0;
    }
  }
  
  
    for (int i=0; i<N; i++)       //agarro la part i
    {
      for (int j=i+1; j<N; j++)
      {
        xdif[0]=(*(x+j*3)-*(x+i*3));    //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES X
        xdif[1]=(*(x+j*3+1)-*(x+i*3+1));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES Y
        modxdif=sqrt(xdif[0]*xdif[0]+xdif[1]*xdif[1]);  //ESTA ES LA DISTANCIA ENTRE LA PARTÍCULA i Y LA j
        seda=rad1+rad1-modxdif; // this is the overlap between i and j at time t-1
        
        if (seda>-1.5)
        {
          if (*(neigh+i*30+29)<29 ) 
          {
            *(neigh+i*30+*(neigh+i*30+29))=j;
            *(neigh+i*30+29)=*(neigh+i*30+29)+1;
            
//             *(neigh+j*30+*(neigh+j*30+29))=i;
//             *(neigh+j*30+29)=*(neigh+j*30+29)+1;
          }   
          else if (*(neigh+i*30+29)>29 ) 
          {
             cout << *(neigh+i*30+29)  << " >29, error "  << endl;
          }
        }
      }
//        cout << *(neigh+i*30+29) << " neighs" << endl;
    }
/*    
        for (int i=0; i<N; i++)       //clean the vector 
        {
          cout << i << " total " << *(neigh+i*30+29) << endl;
          cout << i << " " << *(x+i*3) << " " << *(x+i*3+1) << endl;
          for (int j=0; j<*(neigh+i*30+29) ; j++) 
          {
            k=*(neigh+i*30+j);
            cout << *(neigh+i*30+j) <<" " << *(x+k*3) << " " << *(x+k*3+1) << endl;
          }
          cout << " " << endl;
        }*/
  
  
}

