#include <stdlib.h>
#include <assert.h>
#include "trimatrix.h"

void QRA(trimatrix* T)
{
   // function declarations
   matrix QRdecomp(matrix* A);
   int FindZero(trimatrix* T);
   double GetShift(trimatrix* T);

    // get size
   const int N = T->rows; assert(N==T->cols);

   if (N==1)
   { return; }
   else
   {
      int k = FindZero(T); // see if we can deflate
      if (k==N) // can't deflate
      {
	 // Find shift to improve convergence
	 double mu = GetShift(T);

	 // Copy tridiagonal matrix into a bigger
	 // matrix -- needed for QR step
	 matrix R = new_matrix(N,N);
	 mget(R,1,1) = tget(T,1,1);
	 mget(R,1,2) = tget(T,1,2);
	 for (int i=2; i<=(N-1); i++)
	    {
	       mget(R,i,i-1) = tget(T,i,i-1);
	       mget(R,i,i)   = tget(T,i,i);
	       mget(R,i,i+1) = tget(T,i,i+1);
	    }	 
	 mget(R,N,N-1) = tget(T,N,N-1);
	 mget(R,N,N) = tget(T,N,N);

	 // Subtract shift from bigger matrix
	 for (int i=1; i<=N; i++)
	 { mget(R,i,i) -= mu; }

	 // QR factorization on bigger matrix
	 matrix Q = QRdecomp(&R);

	 // Multiply Q and R in reverse order
	 // and store in a new tridiagonal matrix
	 delete_trimatrix(T);
	 *T = matrix_mult_to_trimatrix(&R,&Q);

	 // Add the shift back in 
	 for (int i=1; i<=N; i++)	 
	 { tset(T,i,i, tget(T,i,i) + mu ); }

	 // Recursive call to QR algorithm
	 QRA(T);
      }
      else
      {
	 // Split big T matrix into 2 submatrices
	 trimatrix T1 = grab_sub_trimatrix(T,1,k);
	 trimatrix T2 = grab_sub_trimatrix(T,k+1,N);

	 // Call QR algorithm on each submatrix
	 QRA(&T1);
	 QRA(&T2);

	 // Merge the result of each submatrix
	 // back into larger matrix T
	 delete_trimatrix(T);
	 *T = merge_sub_trimatrix(&T1,&T2);
	 delete_trimatrix(&T1);
	 delete_trimatrix(&T2);
      }
   }
}
