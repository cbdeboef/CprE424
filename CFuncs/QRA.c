#include "trimatrix.h"

void QRA(trimatrix* T){

	matrix QRdecomp(matrix* A);
	int FindZero(trimatrix* T);
	double GetShift(trimatrix* T);

	const int N = T->rows; assert(N == T->cols);
	if(N == 1){ return;}
	else{
		int k = FindZero(T);
		if(k == N){
			double mu = GetShift(T);

			matrix R = new_matrix(N,N);
			mget(R,1,1) = tget(T,1,1);
			mget(R,1,2) = tget(T,1,2);

			for(int i = 2; i <= (N-1); i++){
				mget(R,i,i-1) = tget(T,i,i-1);
				mget(R,i,i) = tget(T,i,i);
				mget(R,i,i+1) = tget(T,i,i+1);
			}
			mget(R,N,N-1) = tget(T,N,N-1);
			mget(R,N,N) = tget(T,N,N);

			for(int i = 1; i <= N; i++){
				mget(R,i,i) -= mu;
			}

			matrix Q = QRdecomp(&R);

			delete_trimatrix(T);
			*T = matrix_mult_to_trimatrix(&R,&Q);

			for(int i = 1; i <= N; i++){
				tset(T,i,i,tget(T,i,i) + mu);
			}

			QRA(T);
		}
		else{
			trimatrix T1 = grab_sub_trimatrix(T,1,k);
			trimatrix T2 = grab_sub_trimatrix(T,k+1,N);

			QRA(&T1);
			QRA(&T2);

			delete_trimatrix(T);
			*T = merge_sub_trimatrix(&T1,&T2);
			delete_trimatrix(&T1);
			delete_trimatrix(&T2);
		}
	}
}

