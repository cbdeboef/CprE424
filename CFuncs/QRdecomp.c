#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"
/*
This routine will perform QR factorization A = QR to get Q and R of A!
Please do not alter the codes! 
*/

static inline double sign(const double x)
{
   if (x<0.0)
   { return -1.0; }
   else
   { return  1.0; }
}

matrix Householder(matrix* R)
{
   const int N = R->rows;
   assert(N>1); assert(R->cols==N);

   matrix V = new_matrix(N,N);
   vector vtR = new_vector(N);
   
   for (int k=1; k<=N; k++)
   {
      const int s = N-k+1;
      double normX2 = 0.0;
      for (int i=1; i<=s; i++)
      {
	 double tmp = mgetp(R,k-1+i,k);
	 mget(V,i,k) = tmp;
	 normX2 += pow(tmp,2);
      }
      double x1 = mget(V,1,k);
      mget(V,1,k) += sign(x1)*sqrt(normX2);
      double normV = sqrt(normX2-pow(x1,2)+pow(mget(V,1,k),2));
      for (int i=1; i<=s; i++)
      {	mget(V,i,k) = mget(V,i,k)/normV; }

      for (int i=k; i<=N; i++)
      {
	 vget(vtR,i+1-k) = 0.0;
	 for (int j=1; j<=s; j++)
	 { vget(vtR,i+1-k) += mget(V,j,k)*mgetp(R,j+k-1,i); }
      }

      for (int i=k; i<=N; i++)
	 for (int j=k; j<=N; j++)
	 {
	    mgetp(R,i,j) -= 2.0*mget(V,i+1-k,k)*vget(vtR,j+1-k);
	 }
   }

   delete_vector(&vtR);
   return V;
}


matrix QRdecomp(matrix* R)
{
   const int N = R->rows;
   assert(N>1); assert(R->cols==N);

   matrix V = Householder(R);
   
   matrix Q = new_matrix(N,N);
   for (int i=1; i<=N; i++)
   { mget(Q,i,i) = 1.0; }

   for (int k=N; k>=1; k--)
   {
      int s = N-k+1;

      for (int i=1; i<=N; i++)
      {
	 double dotprod = 0.0;
	 for (int ell=1; ell<=s; ell++)
	 { dotprod += mget(V,ell,k)*mget(Q,ell+k-1,i); }
	 
	 for (int j=k; j<=N; j++)
	 {	    
	    mget(Q,j,i) -= 2.0*mget(V,j+1-k,k)*dotprod;
	 }
      }
   }

   return Q;
}
