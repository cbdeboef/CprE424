#ifndef __TRIMATRIX_H__
#define __TRIMATRIX_H__
#include "matrix.h"

typedef struct trimatrix trimatrix;
struct trimatrix{
	int rows; int cols;
	double* left;
	double* center;
	double* right;
};

typedef struct pentamatrix pentamatrix;
struct pentamatrix{
	int rows; int cols;
	double* leftleft;
	double* left;
	double* center;
	double* right;
	double* rightright;
};

#endif
