/**
 * LEAD University
 * Data Science Program
 * BCD-9218: Parallel and Distributed Computing
 * Instructor Diego Jimenez, Eng. (diego.jimenez@ulead.ac.cr)
 *  OpenMP parallel shear sort.
 * Editado por Bernal Rojas
 */

#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"

#define MAX_VALUE 10000

// Shear sort function
void shear_sort(int **A, int M){
 int i, j, k, temp;

   for(i = 0; i < M;) {
      for(j = i+1; j < M; j++) {
         if(A[j] < A[j-1])
			   temp = *A[j];
   				*A[j] = *A[j-1];
   				*A[j-1] = temp;
      }
      M--;
      for(k = M-1; k > i; k--) {
         if(A[k] < A[k-1])
			temp = *A[k];
   			*A[k] = *A[k-1];
   			*A[k-1] = temp;
      }
      i++;
   }

}

// Main method
int main(int argc, char* argv[]) {
	int N, M;
	int **A;
	double elapsedTime;

	// checking parameters
	if (argc != 2 && argc != 3) {
		cout << "Parameters: <N> [<file>]" << endl;
		return 1;
	}
	N = atoi(argv[1]);
	M = (int) sqrt(N);
	if(N != M*M){
		cout << "N has to be a perfect square!" << endl;
		exit(1);
	}

	// allocating matrix A
	A = new int*[M];
	for (int i=0; i<M; i++){
		A[i] = new int[M];
	}

	// reading files (optional)
	if(argc == 3){
		readMatrixFile(A,M,argv[2]);
	} else {
		srand48(time(NULL));
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				A[i][j] = lrand48() % MAX_VALUE;
			}
		}
	}

	// starting timer
	timerStart();

	// calling shear sort function
	shear_sort(A,M);

	// testing the results is correct
	if(argc == 3){
		printMatrix(A,M);
	}

	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds" << std::endl;

	// releasing memory
	for (int i=0; i<M; i++) {
		delete [] A[i];
	}
	delete [] A;

	return 0;
}
