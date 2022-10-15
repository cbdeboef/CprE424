#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "matrix.h"
#include "trimatrix.h"

static inline double sign(const double x)
{
   if (x<0.0)
   { return -1.0; }
   else
   { return  1.0; }
}

void Hessenberg(const matrix* Ain, trimatrix* T)
{
   const int N = Ain->rows; assert(N>1);
   assert(N==Ain->cols);
   assert(N==T->rows); assert(N==T->cols);

   matrix A = new_matrix(N,N);
   for (int i=1; i<=N; i++)
      for (int j=1; j<=N; j++)
      { mget(A,i,j) = mgetp(Ain,i,j); }
   
   vector x = new_vector(N);
   vector v = new_vector(N);
   vector vTH1 = new_vector(N);
   vector Hv2 = new_vector(N);

   // Main loop
   for (int k=1; k<=(N-2); k++)
   {
      // Part 1: Construct reflector vector "v"
      for (int i=(k+1); i<=N; i++)
      { vget(x,i-k) = mget(A,i,k); }

      double normX = 0.0;
      for (int j=1; j<=(N-k); j++)
      { normX += pow(vget(x,j),2); }
      normX = sqrt(normX);

      for (int j=1; j<=(N-k); j++)
      { vget(v,j) = vget(x,j); }
      vget(v,1) = vget(v,1) + sign(vget(x,1))*normX;

      double normV = sqrt(pow(normX,2) - pow(vget(x,1),2)
			  + pow(vget(v,1),2));
      
      for (int j=1; j<=(N-k); j++)
      { vget(v,j) = vget(v,j)/normV; }

      // Part 2: apply reflector to (k+1):N by k:N block of A
      for (int i=1; i<=(N+1-k); i++)
      {
	 vget(vTH1,i) = 0.0;
	 for (int j=(k+1); j<=N; j++)
	 { vget(vTH1,i) += vget(v,j-k)*mget(A,j,i-1+k); }
      }

      for (int i=1; i<=(N-k); i++)
	 for (int j=1; j<=(N+1-k); j++)
	 {
	    int ishift = k+i;
	    int jshift = (k-1)+j;
	    mget(A,ishift,jshift) -=
	       2.0*vget(v,i)*vget(vTH1,j);
	 }
      
      // Part 3: apply reflector to 1:N by (k+1):N block of A
      for (int i=1; i<=N; i++)
      {
	 vget(Hv2,i) = 0.0;
	 for (int j=1; j<=(N-k); j++)
	 { vget(Hv2,i) += mget(A,i,j+k)*vget(v,j); }
      }

      for (int i=1; i<=N; i++)
	 for (int j=1; j<=(N-k); j++)
	 {
	    int ishift = i;
	    int jshift = j+k;
	    mget(A,ishift,jshift) -=
	       2.0*vget(Hv2,i)*vget(v,j);
	 }
   }

   tset(T,1,1,mget(A,1,1));
   tset(T,1,2,mget(A,1,2));
   for (int i=2; i<=(N-1); i++)
   {
      tset(T,i,i-1,mget(A,i,i-1));
      tset(T,i,i,  mget(A,i,i));
      tset(T,i,i+1,mget(A,i,i+1));
   }
   tset(T,N,N-1,mget(A,N,N-1));
   tset(T,N,N,mget(A,N,N));
   
   delete_vector(&x);
   delete_vector(&v);
   delete_vector(&vTH1);
   delete_vector(&Hv2);
   delete_matrix(&A);
}
