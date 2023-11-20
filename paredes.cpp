#include "paredes.hpp"

void walls (const int rad2, const float rad1, const float ancho, const float alto, float *(w00))
{  
*(w00)=0;
*(w00+1)=ancho;  //pared derecha
*(w00+2)=0.;   //pared izquierda
*(w00+3)=-10.;   //second bottom
}


// void walls (const int rad2, const float rad1, const float ancho, const float alto, float *(w00))
// {  
// *(w00)=0;
// *(w00+1)=-rad2;  //piso
// *(w00+2)=ancho+rad2;
// *(w00+3)=alto*rad1;  //pared derecha
// *(w00+4)=-rad2;
// *(w00+5)=*(w00+3);   //pared izquierda
// }

