#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int A[100];
	int B[100];
	int i = 0;
	srand(1234);
	/* Set random seed */
	
	printf("Sequential version\n");
	for (i=0; i < 100; i++){

  		A[i] = (rand()%1000)*10;
 		printf("A[%d] = %d\n", i, A[i]);
	}
	
	/* Set each element randomly to 0-999 */
	
	printf("Parallel version\n");

	int tid;
	#pragma omp parallel
	{
		tid = omp_get_thread_num();
		#pragma omp for
		for (i=0; i < 100; i++){
			A[i] = A[i] * 10;
			printf("Thread num = %d, parallel A[%d] = %d\n", tid,  i, A[i]);
		}
	}
}
