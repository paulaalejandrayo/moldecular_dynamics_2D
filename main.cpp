// esta version incluye torques y velocidades angulares, andando


#include <iostream>
#include <fstream>   
#include <math.h>
#include <algorithm>
#include "paredes.hpp"
#include "record.hpp"
#include "aceleracion.hpp"
#include "posiciones.hpp"
#include "posiciones_old.hpp"
#include "velocidades.hpp"
#include <stdlib.h>
#include <time.h>
#include "inicializa.hpp"
#include <stdio.h>
#include <string.h>
#include "neighbours.hpp"
using namespace std;
// using namespace




FILE *fopen(), *pf;
const int rad_paredes=1000000;
const float rad1=0.5;                      //float es de precisión de 7 dígitos (32 bits) y double de precisión de 15 dígitos (64 bits)
double *parts;
double *vels;
double *ac;
double *dissipation;
double *parts_0;
int  *neigh;

const float Kn=20000000000, gamman=40600, mu=0.5, gammas=20000000, dens=1, g=1, delta=0.000001;  /*h=40,*/ /*ancho=10*rad1;*/ //h=40 unidades
const float mas_1=dens*0.75*rad1, mas_2=dens*0.75*rad_paredes, I1=mas_1*rad1*rad1/2 ;
float wall[3][2];
int N, pasos;
float h, ancho;
string fichero;
int rec=1, flag=0;


int main ( )
{
  pf = fopen("inicializa.ini", "r");
  fscanf(pf, "%d\n", &N);   
  cout << N << "  = número de partículas"<<endl;
  fscanf(pf, "%f\n", &ancho); 
  ancho=ancho*2*rad1;
  cout << ancho << "  = ancho_celda" <<endl;
  fscanf(pf, "%d\n", &pasos); 
  cout << pasos << "  =  pasos" <<endl;
  fscanf(pf, "%f\n", &h); 
  h=h*rad1;
  cout << h << " =  altura centro" <<endl;
  
  
  parts=(double *)malloc((N*3)*sizeof(double)) ;
  vels=(double *)malloc((N*3)*sizeof(double));
  ac=(double *)malloc((N*3)*sizeof(double)) ;
  dissipation=(double *)malloc((N*1)*sizeof(double)) ;
  parts_0=(double *)malloc((N*3)*sizeof(double)) ;
  neigh=(int *)malloc((N*30)*sizeof(int)) ; 
    
  walls (rad_paredes, rad1, ancho, h, &wall[0][0]);
  inicializacion (N, &parts[0], &vels[0], ancho, rad1, h, &dissipation[0], &rec,&neigh[0]); //rec is set to 1 here

  
  
  fichero = "configuraciones.xyz";
  ofstream file(fichero.c_str(), ios::out);
  file.close();
  
  copia_posiciones (N, &parts[0], &parts_0[0]);
//   neighbours (N, rad1, &parts[0], &neigh[0]);
  acs (N, rad_paredes, rad1, g, &ac[0], &parts[0],  &vels[0], &wall[0][0], Kn, gamman, mu, gammas, dens, &rec, &dissipation[0], &parts_0[0], flag, &neigh[0]); // this does not change rec
  record  (0, N, &parts[0],&vels[0], fichero, rad1, &rec, &dissipation[0], g, dens); //rec=1
  
  for (int j=1;j<pasos;j++)
  {
    copia_posiciones (N, &parts[0], &parts_0[0]);
    actualiza_velocidades (N, &ac[0], &vels[0], delta);
    actualiza_posiciones (N, &ac[0], &parts[0], &vels[0], delta);
    if (j%100==0)
    {
      neighbours (N, rad1,  &parts[0], &neigh[0]);
    }
    acs (N, rad_paredes, rad1, g, &ac[0], &parts[0],  &vels[0], &wall[0][0], Kn, gamman, mu, gammas, dens, &rec,  &dissipation[0], &parts_0[0], flag, &neigh[0]);//rec=1
    actualiza_velocidades (N, &ac[0], &vels[0],delta);
    
    if (j==100000000){
        flag=1;
    }
    
    if (j%100000==0)
    {
      record  (j, N, &parts[0], &vels[0],fichero,rad1, &rec, &dissipation[0], g, dens); //rec=1 only the first time, then set to 0
      rec=0;
      cout << j << "  pasos "<< flag << endl;
    }
  }

  
  
  
return 0;
}
