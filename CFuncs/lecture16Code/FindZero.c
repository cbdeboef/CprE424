#include <stdlib.h>
#include <math.h>
#include "trimatrix.h"
/*
This routine will find the zeros in the sub- or super-diagonal of T, which will be used for deflation!
Please do not alter the codes!
*/
int FindZero(trimatrix* T)
{
   const int N = T->rows;
   int k=0;
   int mfound=0;
   double TOL = 1.0e-15;

   while (mfound==0 && k<(N-1))
   {
      k=k+1;
      if (fabs(tget(T,k,k+1))<TOL)
      { mfound = 1; }

   }

   if (mfound==0)
   {
      k=k+1;
   }
   
   return k;
}
