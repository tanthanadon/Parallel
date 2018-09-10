#include <stdio.h>
#include <omp.h>

int main(){
	int i;
	int sum = 0;
        int m = 0;
        int A[100];
        srand(1234);    /* Set random seed */
	
	printf("The number that is greater than or equal to 500 sequentially\n");
        for(i=0; i<100; i++){
                A[i] = (rand()%1000); /*Set each element rndomly to 0-999 */
		if(A[i] >= 500){
			//printf("A[%d] = %d", i, A[i]);
		}
        }
	
	printf("The number that is greater than or equal to 500 by using parallelism\n");
	#pragma omp parallel for
        for(i=0; i<100; i++){
                int tid = omp_get_thread_num();
                if(A[i] >= 500){
                	printf("Thread num = %d, A[%d] = %d\n", tid, i, A[i]);
                }
        }
	
}
