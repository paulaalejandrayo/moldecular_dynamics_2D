#include "inicializa.hpp"


void inicializacion (const int N, double *x, double *v, const float ancho, float rad1, float h,double *dissipation, int *recorded, int *neigh, double *x_N)
{
  int k,j,rep, num1, num2;
  float solapa;
  srand(time(NULL));
  
  
  for (int i=0; i<N; i++)    
  {    
    num1   = rand()%(1000);
    num2   = rand()%(1000);
    *(x+i*3)   = (ancho-2)*num1/1000+2*rad1;           //asigna un valor aleatorio a x e y esta variable esta entre 2 y ancho-2
    *(x+i*3+1) = (2*N*num2/(ancho*1000) + 2*rad1)+h;
    *(x+i*3+2)= 0;                                     //// esta variable esta entre h+2*0.5 radios y 10*N/L+h+0.5 radios
    *(v+i*3)= 0;
    *(v+i*3+1)=0;
    *(v+i*3+2)=0;
    *(dissipation+i)=0;
    
    *(x_N+i*3)  =0;   
    *(x_N+i*3+1)=0;
    *(x_N+i*3+2)=0;

    for (int j=0; j<30; j++){
      *(neigh+i*30+j)=0;
    }
    
    rep=0;           //este contador va a indicar cuando se reppita mucho el proceso para no solapar partículas
    do                  //este bucle va a repetirse mientras la posicion seleccionada solape con alguna partícula existente
    {
      rep++;
      k=1;
      if (i!=0)
      {
	j=0;         //este va a recorrer partículas ya posicionadas
	do
	{
	  if (k==1)      //este bucle lo repite solo mientras no encuentre partículas que solapen
	  {
	    solapa= sqrt((((*(x+i*3))-(*(x+j*3)))*((*(x+i*3))-(*(x+j*3))))+(((*(x+i*3+1))-(*(x+j*3+1)))*((*(x+i*3+1))-(*(x+j*3+1))))) ;
	    if (solapa < 2*rad1 )
	    {
	      num1   = rand()%(1000);                //asigna nuevos valores a x e y si las anteriores solapaban con una prtícula
	      num2   = rand()%(1000);
	      *(x+i*3)   = (ancho-2)*num1/1000+2*rad1;  
	      *(x+i*3+1) = 2*N*num2/(ancho*1000) + 2*rad1;	//esta variable esta entre   
	      k=0;
	    }
	  }
	  j++;
	}      while (k==1 && j<i  );
      }
      if (rep > 100)
      {
	cout << rep << "  intentos para la partícula " << i << endl;
      }      
    }  while (k==0);
  }
  *recorded=1;
  cout<<"completo N = " << N << endl;
}
    
