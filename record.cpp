#include "record.hpp"

void record  (int j, const int N, double *x, double *v, string fp, const float rad1,  int *recorded, double *dissipation, double g, double dens)
{
  double ke, m, pe;
  ofstream file(fp.c_str(), ios::app);
  
  file<<  "ITEM: TIMESTEP"<< endl;
  file<<   j  << endl;
  file<<  "ITEM: NUMBER OF ATOMS"<< endl;
  file << 2*N /*<< " \t " << j */<< endl;
  file<<  "ITEM: BOX BOUNDS pp ff mm  "<< endl;
  file<<  "-0.012 0.012  "<< endl;
  file<<  "-0.0035 0.0035  "<< endl;
  file<<  "-0.005 0.7  "<< endl;
  file<<  "ITEM: ATOMS id radius type x y z diss ke pe ke+pe diss-pe-ke"<< endl;
  for (int i=0; i<N; i++)
  {
    m=4./3*3.1416*rad1*rad1*rad1*dens;
    ke=m/2.*( (*(v+i*3))*(*(v+i*3))+(*(v+i*3+1))*(*(v+i*3+1)));
    pe=*(x+i*3+1)*g*m;
//     file << pe   << " \t " << ke   <<    "\t"  << *(dissipation+i) << endl;
    file << i+1   << " \t " << rad1      << " \t " << "1" << " \t " << *(x+i*3)                        << " \t " << *(x+i*3+1)                         <<" \t " << rad1*2  <<" \t " << *(dissipation+i) <<" \t " << ke  << " \t " << pe <<" \t " <<  pe+ke << " \t " << *(dissipation+i)+(pe+ke) <<  " \t "<< endl;
    file << i+1+N << " \t " << rad1*0.01 << " \t " << "2" << " \t " << *(x+i*3)-rad1*cos(*(x+i*(3)+2)) << " \t " << *(x+i*3+1)+rad1*sin(*(x+i*(3)+2))  << " \t "<< rad1*2  << " \t "<< *(dissipation+i) << " \t " << ke << " \t " << pe << " \t " << pe+ke << " \t " << *(dissipation+i)+(pe+ke) <<  " \t " << endl;    
  }
  file.close();
}


 /*fuerzas[i][0] << " \t " << fuerzas[i][1]<< " \t " << ac[i][0]<< " \t "<< ac[i][1]  << " \t "<< seda */ 
// VER COMO HAGO PARA USAR EL ARCHIVO QUE LE ESTOY PASANDO
