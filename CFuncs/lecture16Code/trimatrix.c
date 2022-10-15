#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "trimatrix.h"

trimatrix new_trimatrix(const int rows)
{
   trimatrix trimat;
   assert(rows>0);
   trimat.rows   = rows;
   trimat.cols   = rows;
   trimat.left   = (double*)malloc(sizeof(double)*rows);
   trimat.center = (double*)malloc(sizeof(double)*rows);
   trimat.right  = (double*)malloc(sizeof(double)*rows);

   for (int i=0; i<(rows); i++)
   {
      trimat.left[i]   = 0.0;
      trimat.center[i] = 0.0;
      trimat.right[i]  = 0.0;
   }
	 
   return trimat;
}

void delete_trimatrix(trimatrix* t)
{
   free(t->left);
   free(t->center);
   free(t->right);
}

void print_trimatrix_full(const trimatrix* trimat, char* varname)
{
   assert(trimat->rows==trimat->cols);
   assert(trimat->rows>0);
   printf("\n %.100s =\n", &varname[1] );
   
   for(int i=1; i<=trimat->rows; i++ )
   {
      printf("  |  ");
      for(int j=1; j<=trimat->cols; j++) 
      {
	 double tmp = tget(trimat,i,j);
	 if (fabs(tmp)<1.0e-14)
	 { tmp = 0.0; }
	 printf("%13.6e",tmp);
	 if (j<trimat->cols) {printf(", ");}
	 else {printf(" ");}
      }
      printf("|\n");
   }
   printf("\n");
}

double tget(const trimatrix* trimat, const int i, const int j)
{
   if (i==j)
   {  return trimat->center[i-1];  }
   else if (i==(j+1))
   {  return trimat->left[i-1];    }
   else if (i==(j-1))
   {  return trimat->right[i-1];   }
   else
   {  return 0.0; }
}

void tset(trimatrix* trimat, const int i, const int j,
	  const double val)
{
   if (i==j)
   {  trimat->center[i-1] = val;  }
   else if (i==(j+1))
   {  trimat->left[i-1]   = val;  }
   else if (i==(j-1))
   {  trimat->right[i-1]  = val;  }
}

trimatrix trimatrix_add(const trimatrix* A, const trimatrix* B)
{
   const int rows = A->rows;
   const int cols = A->cols;
   assert(rows==cols);
   assert(rows==B->rows);
   assert(cols==B->cols);
   trimatrix C = new_trimatrix(rows);

   for (int i=1; i<=rows; i++)
      for (int j=1; j<=cols; j++)
      {
         tset(&C,i,j, tget(A,i,j)+tget(B,i,j) );
      }

   return C;
}

trimatrix trimatrix_sub(const trimatrix* A, const trimatrix* B)
{
   const int rows = A->rows;
   const int cols = A->cols;
   assert(rows==cols);
   assert(rows==B->rows);
   assert(cols==B->cols);
   trimatrix C = new_trimatrix(rows);

   for (int i=1; i<=rows; i++)
      for (int j=1; j<=cols; j++)
      {
         tset(&C,i,j, tget(A,i,j)-tget(B,i,j) );
      }

   return C;
}

trimatrix trimatrix_dot_mult(const trimatrix* A, const trimatrix* B)
{
   const int rows = A->rows;
   const int cols = A->cols;
   assert(rows==cols);
   assert(rows==B->rows);
   assert(cols==B->cols);
   trimatrix C = new_trimatrix(rows);

   for (int i=1; i<=rows; i++)
      for (int j=1; j<=cols; j++)
      {
	 tset(&C,i,j, tget(A,i,j)*tget(B,i,j) );
      }
	 
   return C;
}

vector trimatrix_vector_mult(const trimatrix* A, const vector* x)
{
   const int rows = A->rows; const int cols = A->cols;
   const int size = x->size;
   assert(rows==cols); assert(cols==size);
   vector Ax = new_vector(rows);
   double tmp;

   tmp = 0.0;
   for (int j=1; j<=2; j++)
   { tmp += tget(A,1,j)*vgetp(x,j); }
   vget(Ax,1) = tmp;
   
   for (int i=2; i<=(rows-1); i++)
   {
      tmp = 0.0;
      for (int j=(i-1); j<=(i+1); j++)
      { tmp += tget(A,i,j)*vgetp(x,j); }
      vget(Ax,i) = tmp;
   }

   tmp = 0.0;
   for (int j=(rows-1); j<=rows; j++)
   { tmp += tget(A,rows,j)*vgetp(x,j); }
   vget(Ax,rows) = tmp;

   return Ax;
}

vector trisolve(const trimatrix* A, const vector* b)
{
   const int rows = A->rows; const int cols = A->cols;
   const int N = b->size;
   assert(rows==cols); assert(rows==N);

   // copy tridiagonal matrix into a pentadiagonal matrix
   pentamatrix Afive = new_pentamatrix(N);
   for (int i=1; i<=N; i++)
   {
      const int jstart = (i-1)*(i>1) + (i<=1)*1;
      const int jend   = (i+1)*(i<N) + (i>=N)*N;
      for (int j=jstart; j<=jend; j++)
      {
	 pentaset(&Afive,i,j, tget(A,i,j) );
      }
   }

   vector x = new_vector(rows);

   for (int i=1; i<=(N-1); i++) // LOOP OVER EACH COLUMN
   {
      // Select largest pivot in current column
      int p=i; double maxA = -100.0e0;
      for (int j=i; j<=(i+1); j++)
      {
	 double tmp = fabs(pentaget(&Afive,j,i));
         if ( tmp > maxA ){ p = j; maxA = tmp; }
      }

      // See if matrix is singular
      if (maxA <= 1.0e-14)
      { printf(" Cannot invert system\n"); exit(1); }

      // Pivot (aka interchange rows)
      if (p!=i)
      {
	 const int jstart = (i-2)*(i>2) + (i<=2)*1;
	 const int jend   = (i+2)*(i<(N-1)) + (i>=(N-1))*N;
         for (int j=jstart; j<=jend; j++)
         {
            double tmp1  = pentaget(&Afive,i,j);
	    pentaset(&Afive,i,j, pentaget(&Afive,p,j) );
	    pentaset(&Afive,p,j, tmp1 );
         }

         double tmp2 = vgetp(b,i);
	 vgetp(b,i) = vgetp(b,p); vgetp(b,p) = tmp2;
      }

      // Eliminate below diagonal
      {
	 const int jend = (i+2)*(i<(N-1)) + (i>=(N-1))*N;
	 for (int j=(i+1); j<=jend; j++)
	 {
	    double dm = pentaget(&Afive,j,i)/pentaget(&Afive,i,i);
	    const int kend = (j<=(N-2))*(i+2) + N*(j>N-2);
	    for (int k=(i+1); k<=kend; k++)
	    { pentaset(&Afive,j,k,  pentaget(&Afive,j,k) - dm*pentaget(&Afive,i,k) ); }
	    vgetp(b,j) = vgetp(b,j) - dm*vgetp(b,i);
	 }
      }
   }

   // Backward substitution
   vget(x,N) = vgetp(b,N)/pentaget(&Afive,N,N);
   for (int j=1; j<=(N-1); j++)
   {
      double sum = 0.0e0;

      const int kend = (j>1)*(N-j+2) + (j==1)*N;
      for (int k=(N-j+1); k<=kend; k++)
      { sum = sum + pentaget(&Afive,N-j,k)*vget(x,k); }

      vget(x,N-j) = (vgetp(b,N-j) - sum)
	 /pentaget(&Afive,N-j,N-j);
   }

   delete_pentamatrix(&Afive);
   return x;
}

pentamatrix new_pentamatrix(const int rows)
{
   pentamatrix p;
   assert(rows>0);
   p.rows   = rows;
   p.cols   = rows;
   p.leftleft   = (double*)malloc(sizeof(double)*rows);
   p.left   = (double*)malloc(sizeof(double)*rows);
   p.center = (double*)malloc(sizeof(double)*rows);
   p.right  = (double*)malloc(sizeof(double)*rows);
   p.rightright  = (double*)malloc(sizeof(double)*rows);

   for (int i=0; i<(rows); i++)
   {
      p.leftleft[i]   = 0.0;
      p.left[i]   = 0.0;
      p.center[i] = 0.0;
      p.right[i]  = 0.0;
      p.rightright[i]   = 0.0;
   }
	 
   return p;
}

void delete_pentamatrix(pentamatrix* p)
{
   free(p->leftleft);
   free(p->left);
   free(p->center);
   free(p->right);
   free(p->rightright);
}

void print_pentamatrix_full(const pentamatrix* p, char* varname)
{
   assert(p->rows==p->cols);
   assert(p->rows>0);
   printf("\n %.100s =\n", &varname[1] );
   
   for(int i=1; i<=p->rows; i++ )
   {
      printf("  |  ");
      for(int j=1; j<=p->cols; j++) 
      {
	 printf("%10.3e",pentaget(p,i,j));
	 if (j<p->cols) {printf(", ");}
	 else {printf(" ");}
      }
      printf("|\n");
   }
   printf("\n");
}

double pentaget(const pentamatrix* p, const int i, const int j)
{
   if (i==j)
   {  return p->center[i-1];  }
   else if (i==(j+1))
   {  return p->left[i-1];    }
   else if (i==(j-1))
   {  return p->right[i-1];   }
   else if (i==(j+2))
   {  return p->leftleft[i-1];   }
   else if (i==(j-2))
   {  return p->rightright[i-1];   }
   else
   {  return 0.0; }
}

void pentaset(pentamatrix* p, const int i, const int j, const double val)
{
   if (i==j)
   {  p->center[i-1] = val;  }
   else if (i==(j+1))
   {  p->left[i-1]   = val;  }
   else if (i==(j-1))
   {  p->right[i-1]  = val;  }
   else if (i==(j+2))
   {  p->leftleft[i-1]   = val;  }
   else if (i==(j-2))
   {  p->rightright[i-1]  = val;  }
}

trimatrix grab_sub_trimatrix(trimatrix* T, int k1, int k2)
{
   const int size = k2-k1+1;
   assert(T->rows>0); assert(k1>0);
   assert(k2>=k1); assert(k2<=T->rows);
   
   trimatrix Tnew = new_trimatrix(size);
   const int shift = k1-1;
   
   tset(&Tnew,1,1, tget(T,1+shift,1+shift));
   tset(&Tnew,1,2, tget(T,1+shift,2+shift));
   for (int i=2; i<=(size-1); i++)
   {
      tset(&Tnew,i,i-1, tget(T,i+shift,i+shift-1));
      tset(&Tnew,i,i,   tget(T,i+shift,i+shift));
      tset(&Tnew,i,i+1, tget(T,i+shift,i+shift+1));
   }
   tset(&Tnew,size,size-1, tget(T,size+shift,size+shift-1));
   tset(&Tnew,size,size,   tget(T,size+shift,size+shift));   

   return Tnew;
}

trimatrix merge_sub_trimatrix(trimatrix* T1, trimatrix* T2)
{
   const int k1 = T1->rows; assert(k1>0);   
   const int k2 = T2->rows; assert(k2>0);
   const int N = k1+k2;

   trimatrix T = new_trimatrix(N);

   tset(&T,1,1, tget(T1,1,1) );
   tset(&T,1,2, tget(T1,1,2) );
   for (int i=2; i<=(k1-1); i++)
   {
      tset(&T,i,i-1, tget(T1,i,i-1) );
      tset(&T,i,i,   tget(T1,i,i) );
      tset(&T,i,i+1, tget(T1,i,i+1) );
   }
   tset(&T,k1,k1-1, tget(T1,k1,k1-1) );
   tset(&T,k1,k1,   tget(T1,k1,k1) );

   tset(&T,k1+1,k1+1, tget(T2,1,1) );
   tset(&T,k1+1,k1+2, tget(T2,1,2) );
   for (int i=2; i<=(k2-1); i++)
   {
      tset(&T,k1+i,k1+i-1, tget(T2,i,i-1) );
      tset(&T,k1+i,k1+i,   tget(T2,i,i) );
      tset(&T,k1+i,k1+i+1, tget(T2,i,i+1) );
   }
   tset(&T,k1+k2,k1+k2-1, tget(T2,k2,k2-1) );
   tset(&T,k1+k2,k1+k2,   tget(T2,k2,k2) );
   
   return T;
}

trimatrix matrix_mult_to_trimatrix(const matrix* A, const matrix* B)
{
   const int N = A->rows; const int colsA = A->cols;
   const int rowsB = B->rows; const int colsB = B->cols;
   assert(colsA==N);
   assert(rowsB==N);
   assert(colsB==N);
   trimatrix C = new_trimatrix(N);
   
   matrix Btranspose = new_matrix(N,N);
   for (int i=1; i<=N; i++)
      for (int j=1; j<=N; j++)
      {
	 mget(Btranspose,i,j) = mgetp(B,j,i);
      }
   
   for (int i=1; i<=N; i++)
   {
      const int jstart = (i>1)*(i-1) + (i==1)*1;
      const int   jend = (i<N)*(i+1) + (i==N)*N;
      for (int j=jstart; j<=jend; j++)
	 for (int k=1; k<=N; k++)
	 {
	    tset(&C,i,j, tget(&C,i,j)
		 + mgetp(A,i,k)*mget(Btranspose,j,k) );
	 }
   }

   delete_matrix(&Btranspose);
   
   return C;
}
