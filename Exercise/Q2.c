#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int i;
	int sum = 0;
	int m = 0;
 	int A[100];
  	srand(1234);    /* Set random seed */
  	printf("Seqential version");
	for(i=0; i<100; i++){
		A[i] = rand()%1000;
		sum += A[i];
		//printf("A[%d] = %d, total = %d\n", i, A[i], sum);
	}
	
	printf("Summation by general computing = %d\n", sum);
	
	sum = 0;
	int tid;
	printf("Parallel version");
	#pragma omp parallel for reduction(+: sum)
  		for(i=0; i<100; i++){
			int tid = omp_get_thread_num();
        		sum += A[i];
			printf("Thread num[%d], A[%d] = %d, total = %d\n", tid, i, A[i], sum);
		}
	printf("Summation by using parallel = %d\n", sum);

}
