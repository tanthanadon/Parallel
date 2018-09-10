

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100
#define T 4
int main(){
	int i;
	int sum = 0;
        int m = 0;
        int A[N];
        srand(1234);    /* Set random seed */
        printf("Seqential version");
        for(i=0; i<100; i++){
                A[i] = rand()%1000;
                sum += A[i];
                //printf("A[%d] = %d, total = %d\n", i, A[i], sum);
        }

	printf("Summation by general computing = %d\n", sum);

        sum = 0;
        printf("Parallel version");
		//Seperate i and Shared sum variable
		#pragma omp parallel private(i) shared(sum) num_threads(T)
		{
			int chunkSize = N/T;
			int tid = omp_get_thread_num();
			int start = tid*chunkSize;
			int end = (tid+1)*chunkSize -1;
               		int subsum = 0;
			for(i = start; i <= end; i++){
				subsum += A[i];
			}
			
			// Sum all subsum
			#pragma omp critical
			sum += subsum;
		}
	printf("Summation by using parallel = %d\n", sum);

}

