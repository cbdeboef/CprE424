#ifndef __TRIMATRIX_H__
#define __TRIMATRIX_H__
#include "matrix.h"
typedef struct trimatrix trimatrix;
struct trimatrix
{
   int rows; int cols;
   double* left;
   double* center;
   double* right;
};
typedef struct pentamatrix pentamatrix;
struct pentamatrix
{
   int rows; int cols;
   double* leftleft;
   double* left;
   double* center;
   double* right;
   double* rightright;
};
// Shortcut evaluate functions
#define print_trimatrix(t) print_trimatrix_full(t,#t)
#define print_pentamatrix(p) print_pentamatrix_full(p,#p)
// Function declarations
trimatrix new_trimatrix(const int);
void delete_trimatrix(trimatrix* t);
double tget(const trimatrix*,const int,const int);
void tset(trimatrix*,const int,const int,const double);
void print_trimatrix_full(const trimatrix*,char*);
trimatrix trimatrix_add(const trimatrix*,const trimatrix*);
trimatrix trimatrix_sub(const trimatrix*,const trimatrix*);
trimatrix trimatrix_dot_mult(const trimatrix*,
			     const trimatrix*);
vector trimatrix_vector_mult(const trimatrix*,const vector*);
vector trisolve(const trimatrix*,const vector*);
pentamatrix new_pentamatrix(const int);
void delete_pentamatrix(pentamatrix* p);
void print_pentamatrix_full(const pentamatrix*,char*);
double pentaget(const pentamatrix*,const int,const int);
void pentaset(pentamatrix*,const int,const int,const double);
trimatrix grab_sub_trimatrix(trimatrix* T, int k1, int k2);
trimatrix merge_sub_trimatrix(trimatrix* T1, trimatrix* T2);
trimatrix matrix_mult_to_trimatrix(const matrix* A, const matrix* B);
#endif
