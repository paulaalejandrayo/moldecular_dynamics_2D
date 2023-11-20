#include "aceleracion.hpp"
#include "neighbours.hpp"
// #include "aceleracion_walss.hpp"
void acs (const int N, const int rad_paredes, const float rad1, const float g, double *ac, double *x,  double *vel, float *w00, const float Kn, const float gamman, const float mu, const float gammas, const float dens,  int *recorded, double *dissipation, double *x_0, int flag, int *neigh)
{
     
  double xdif[2], vdif[2],v_proy ,v_prox, modxdif, fuerzas[N][3], dissT[N], diss;
  double fuerzan, fuerzt, seda,  fuerzanw, fuerztw;
//   const float mas_1=dens*0.75*rad1, I1=mas_1*rad1*rad1/2 ;
  const float mas_1=4./3*3.1416*rad1*rad1*rad1*dens, I1=mas_1*rad1*rad1/2 ;
  double seda_old, xdif_0[2],modxdif_0, Dn, Dt;
  int j;
  
    
  for (int i=0; i<N; i++)       //inicializo fuerzas
  {
    diss=0.0;
    fuerzas[i][0]= 0.0;
    fuerzas[i][1]= 0.0;
    fuerzas[i][2]= 0.0;  
    dissT[i]=0.0;
    if (*recorded==0) {
      *(dissipation+i)=0.0;
    }
  }

  for (int i=0; i<N; i++)       //agarro la part i
  {
//     for (int j=i+1; j<N; j++)
    for (int k=0; k< *(neigh+i*30+29) ; k++) //going through neighbour list
    {
      j=*(neigh+i*30+k);
      
//       cout << i << "  " << j <<  endl;
      
      diss=0.0;
      xdif[0]=(*(x+j*3)-*(x+i*3));    //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES X
      xdif[1]=(*(x+j*3+1)-*(x+i*3+1));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES Y
      modxdif=sqrt(xdif[0]*xdif[0]+xdif[1]*xdif[1]);  //ESTA ES LA DISTANCIA ENTRE LA PARTÍCULA i Y LA j
      seda=rad1+rad1-modxdif; // this is the overlap between i and j at time t-1
      
      if (seda>0.0)
      {
        xdif_0[0]=(*(x_0+j*3)-*(x_0+i*3));    //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES X
        xdif_0[1]=(*(x_0+j*3+1)-*(x_0+i*3+1));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES Y
        modxdif_0=sqrt(xdif_0[0]*xdif_0[0]+xdif_0[1]*xdif_0[1]);  //ESTA ES LA DISTANCIA ENTRE LA PARTÍCULA i Y LA j at time - 1

        seda_old=rad1+rad1-modxdif_0; // this is the overlap between i and j at time t-1
        Dn=  abs(seda-seda_old); 
        Dt=abs(xdif_0[0]*xdif[1]/modxdif_0 - xdif_0[1]* xdif[0]/modxdif_0);
        
        vdif[0]= *(vel+i*3)-*(vel+j*3);
        vdif[1]= *(vel+i*3+1)-*(vel+j*3+1);
        v_prox = vdif[0]*xdif[0]/modxdif + vdif[1]* xdif[1]/modxdif;  //VELOCIDAD PROYECTADA EN LA DIRECCION NORMAL
        v_proy = (vdif[0]*xdif[1]/modxdif - vdif[1]* xdif[0]/modxdif)+(*(vel+i*3+2)+*(vel+j*3+2))*rad1;	  
        fuerzan= -Kn*seda-gamman*v_prox;  //fuerza noraml
        diss=Dn*abs(gamman*v_prox);
        
        if (v_proy!=0.0)
        {
          fuerzt=-1*(v_proy/fabs(v_proy))*min(fabs(mu*fuerzan),fabs(gammas*v_proy)); 
          diss=diss+Dt*min(fabs(mu*fuerzan),fabs(gammas*v_proy)) ;
        }
        else 
        {
          fuerzt=0.0;
        }

      fuerzas[i][0]= fuerzas[i][0]+ (fuerzan*xdif[0]+fuerzt*xdif[0])/modxdif;  //descompongo las fuerzas en las direcciones x e y y calculo los torques
      fuerzas[i][1]= fuerzas[i][1]+ (fuerzan*xdif[1]+fuerzt*xdif[1])/modxdif;
      fuerzas[i][2]= fuerzas[i][2]+ fuerzt*rad1;      
      fuerzas[j][0]= fuerzas[j][0]- (fuerzan*xdif[0]+fuerzt*xdif[0])/modxdif;  //tercera ley
      fuerzas[j][1]= fuerzas[j][1]- (fuerzan*xdif[1]+fuerzt*xdif[1])/modxdif;
      fuerzas[j][2]= fuerzas[j][2]+ fuerzt*rad1;  
      
      dissT[i]= dissT[i]+diss;
      dissT[j]= dissT[j]+diss;
    }
  }
    
		  //hasta aca recorri las particulas
//////////////////////////////////////////////////////////////////////////////////	
  //rigth wall         

      xdif[0]=*(w00+1)-*(x+i*3); //left wall
      xdif[1]=0.0;
      modxdif=abs(xdif[0]);
      seda=rad1-modxdif;
      if (seda>0)
      {

        xdif_0[0]=(*(w00+1)-*(x_0+i*3));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES X
        modxdif_0=abs(xdif_0[0]);  //ESTA ES LA DISTANCIA ENTRE LA PARTÍCULA i Y LA j at time - 1

        seda_old=rad1-modxdif_0; // this is the overlap between i and j at time t-1
        Dn=  abs(seda-seda_old); 
        Dt=abs(*(x_0+i*3+1)-*(x+i*3+1)); //abs(xdif_0[0]*xdif[1]/modxdif_0 - xdif_0[1]* xdif[0]/modxdif_0);
        
        
        vdif[0] = *(vel+i*3);   //-0  walls are not moving           
        vdif[1] = *(vel+i*3+1) ; //- 0
        v_prox = vdif[0]*xdif[0]/modxdif + vdif[1]* xdif[1]/modxdif; //VELOCIDAD PROYECTADA EN LA DIRECCION NORMAL
        v_proy = (vdif[0]*xdif[1]/modxdif - vdif[1]* xdif[0]/modxdif)+(*(vel+i*3+2))*rad1;	
        fuerzanw= -Kn*seda-gamman*v_prox;	
      
        diss=diss+Dn*abs(gamman*v_prox);
        if (v_proy!=0)
        {
          fuerztw=-1*(v_proy/fabs(v_proy))*min(fabs(mu*fuerzanw),fabs(gammas*v_proy));
          diss=diss+Dt*min(fabs(mu*fuerzanw),fabs(gammas*v_proy)) ;
        }
        else
        {
          fuerztw=0.0;
        }
      
      fuerzas[i][0]= fuerzas[i][0]+ (fuerzanw*xdif[0]+fuerztw*xdif[0])/modxdif;
      fuerzas[i][1]= fuerzas[i][1]+ (fuerzanw*xdif[1]+fuerztw*xdif[1])/modxdif;
      fuerzas[i][2]= fuerzas[i][2]+ fuerztw*rad1;  
      
      dissT[i]= dissT[i]+diss;
      }
      
// // //////////////////////
// left wall
      xdif[0]=*(w00+2)-*(x+i*3); //left wall
      xdif[1]=0.0;
      modxdif=abs(xdif[0]);
      seda=rad1-modxdif;
      if (seda>0)
      {

        xdif_0[0]=(*(w00+2)-*(x_0+i*3));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES X
        modxdif_0=abs(xdif_0[0]);  //ESTA ES LA DISTANCIA ENTRE LA PARTÍCULA i Y LA j at time - 1

        seda_old=rad1-modxdif_0; // this is the overlap between i and j at time t-1
        Dn=  abs(seda-seda_old); 
        Dt=abs(*(x_0+i*3+1)-*(x+i*3+1)); //abs(xdif_0[0]*xdif[1]/modxdif_0 - xdif_0[1]* xdif[0]/modxdif_0);
        
        
        vdif[0] = *(vel+i*3);   //-0  walls are not moving           
        vdif[1] = *(vel+i*3+1) ; //- 0
        v_prox = vdif[0]*xdif[0]/modxdif + vdif[1]* xdif[1]/modxdif; //VELOCIDAD PROYECTADA EN LA DIRECCION NORMAL
        v_proy = (vdif[0]*xdif[1]/modxdif - vdif[1]* xdif[0]/modxdif)+(*(vel+i*3+2))*rad1;	
        fuerzanw= -Kn*seda-gamman*v_prox;	
      
        diss=diss+Dn*abs(gamman*v_prox);
        if (v_proy!=0)
        {
          fuerztw=-1*(v_proy/fabs(v_proy))*min(fabs(mu*fuerzanw),fabs(gammas*v_proy));
          diss=diss+Dt*min(fabs(mu*fuerzanw),fabs(gammas*v_proy)) ;
        }
        else
        {
          fuerztw=0.0;
        }
      
      fuerzas[i][0]= fuerzas[i][0]+ (fuerzanw*xdif[0]+fuerztw*xdif[0])/modxdif;
      fuerzas[i][1]= fuerzas[i][1]+ (fuerzanw*xdif[1]+fuerztw*xdif[1])/modxdif;
      fuerzas[i][2]= fuerzas[i][2]+ fuerztw*rad1;  
      
      dissT[i]= dissT[i]+diss;
      }  
    //////////////////////
    //bottom wall
    
    
    

      
    const double RAD=2.5, center=(*(w00+1)-*(w00+2))/2.;

  if (flag==1) {    
    if (*(x+i*3)<(center-RAD) || *(x+i*3)>(center+RAD)) 
    { 
      xdif[0]=0.0; //*(w00)-(*(x+i*3)) ;
    } else {
      if (*(x+i*3)< center ){
          xdif[0]=((center-RAD)-*(x+i*3)) ; //*(w00)-(*(x+i*3)) ;
      } else if (*(x+i*3) >= center)
      {
          xdif[0]=((center+RAD)-*(x+i*3)) ;  //*(w00)-(*(x+i*3)) ;
      }
    }
  } else 
  {
    xdif[0]=0.0;
  }
      xdif[1]=*(w00)-*(x+i*3+1) ; // bottom wall
      modxdif=sqrt(xdif[0]*xdif[0]+xdif[1]*xdif[1]);
      
      seda=rad1-modxdif;
      if (seda>0)
      {
        if (flag==1) {
          if (*(x+i*3)<(center-RAD) || *(x+i*3)>(center+RAD)) 
          { 
            xdif_0[0]=0.0; //*(w00)-(*(x+i*3)) ;
          } else {
            if (*(x+i*3)< center ){
                xdif_0[0]=((center-RAD)-*(x_0+i*3)) ; //*(w00)-(*(x+i*3)) ;
            } else if (*(x+i*3) >= center)
            {
                xdif_0[0]=((center+RAD)-*(x_0+i*3)) ;  //*(w00)-(*(x+i*3)) ;
            }
          }
        } else 
        {
          xdif_0[0]=0;
        }
        
        xdif_0[1]=(*(w00)-*(x_0+i*3+1));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES Y
        modxdif_0=sqrt(xdif_0[0]*xdif_0[0]+xdif_0[1]*xdif_0[1]); 

        seda_old=rad1-modxdif_0; // this is the overlap between i and j at time t-1
        Dn=  abs(seda-seda_old); 
        Dt=abs(*(x_0+i*3)-*(x+i*3)); //abs(xdif_0[0]*xdif[1]/modxdif_0 - xdif_0[1]* xdif[0]/modxdif_0);
        
        vdif[0] = *(vel+i*3);   //-0  walls are not moving           
        vdif[1] = *(vel+i*3+1) ; //- 0
        v_prox = vdif[0]*xdif[0]/modxdif + vdif[1]* xdif[1]/modxdif; //VELOCIDAD PROYECTADA EN LA DIRECCION NORMAL
        v_proy = (vdif[0]*xdif[1]/modxdif - vdif[1]* xdif[0]/modxdif)+(*(vel+i*3+2))*rad1;	 
        fuerzanw= -Kn*seda-gamman*v_prox;	
        
 
        diss=diss+Dn*abs(gamman*v_prox);
//         cout << Dn << "  = Dn " << diss << "  = diss"<<endl;
                
        if (v_proy!=0)
        {
          fuerztw=-1*(v_proy/fabs(v_proy))*min(fabs(mu*fuerzanw),fabs(gammas*v_proy));
          diss=diss+Dt*min(fabs(mu*fuerzanw),fabs(gammas*v_proy)) ;
        }
        else
        {
          fuerztw=0.0;
        }
      
      fuerzas[i][0]= fuerzas[i][0]+ (fuerzanw*xdif[0]+fuerztw*xdif[0])/modxdif;
      fuerzas[i][1]= fuerzas[i][1]+ (fuerzanw*xdif[1]+fuerztw*xdif[1])/modxdif;
      fuerzas[i][2]= fuerzas[i][2]+ fuerztw*rad1;  
      
      dissT[i]= dissT[i]+diss;
      }

    //////////////////////
    //other bottom wall

 

      xdif[0]=0.0;
      xdif[1]=*(w00+3)-*(x+i*3+1) ; // bottom wall
      modxdif=sqrt(xdif[0]*xdif[0]+xdif[1]*xdif[1]);
      
      seda=rad1-modxdif;
      if (seda>0)
      {

        xdif_0[0]=0;

        
        xdif_0[1]=(*(w00)-*(x_0+i*3+1));   //ESTA ES LA DIFERENCIA ENTRE LOS VALORES DE LAS COMPONENTES Y
        modxdif_0=sqrt(xdif_0[0]*xdif_0[0]+xdif_0[1]*xdif_0[1]); 

        seda_old=rad1-modxdif_0; // this is the overlap between i and j at time t-1
        Dn=  abs(seda-seda_old); 
        Dt=abs(*(x_0+i*3)-*(x+i*3)); //abs(xdif_0[0]*xdif[1]/modxdif_0 - xdif_0[1]* xdif[0]/modxdif_0);
        
        vdif[0] = *(vel+i*3);   //-0  walls are not moving           
        vdif[1] = *(vel+i*3+1) ; //- 0
        v_prox = vdif[0]*xdif[0]/modxdif + vdif[1]* xdif[1]/modxdif; //VELOCIDAD PROYECTADA EN LA DIRECCION NORMAL
        v_proy = (vdif[0]*xdif[1]/modxdif - vdif[1]* xdif[0]/modxdif)+(*(vel+i*3+2))*rad1;	 
        fuerzanw= -Kn*seda-gamman*v_prox;	
        
 
        diss=diss+Dn*abs(gamman*v_prox);
//         cout << Dn << "  = Dn " << diss << "  = diss"<<endl;
                
        if (v_proy!=0)
        {
          fuerztw=-1*(v_proy/fabs(v_proy))*min(fabs(mu*fuerzanw),fabs(gammas*v_proy));
          diss=diss+Dt*min(fabs(mu*fuerzanw),fabs(gammas*v_proy)) ;
        }
        else
        {
          fuerztw=0.0;
        }
      
      fuerzas[i][0]= fuerzas[i][0]+ (fuerzanw*xdif[0]+fuerztw*xdif[0])/modxdif;
      fuerzas[i][1]= fuerzas[i][1]+ (fuerzanw*xdif[1]+fuerztw*xdif[1])/modxdif;
      fuerzas[i][2]= fuerzas[i][2]+ fuerztw*rad1;  
      
      dissT[i]= dissT[i]+diss;
      }      
      
// // //////////////////////
    
    
    
    

    *(ac+i*3) = fuerzas[i][0]/mas_1;
    *(ac+i*3+1) = fuerzas[i][1]/mas_1-g;
    *(ac+i*3+2) = fuerzas[i][2]/I1;
    *(dissipation+i) =*(dissipation+i)+ dissT[i];    
  }
        if (*recorded==0) {
          *recorded=1;
       }
}
