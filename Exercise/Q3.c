#include <stdio.h>
#include <omp.h>

int main(){
	int i;
	int sum = 0;
        int m = 0;
        int A[100];
        srand(1234);    /* Set random seed */
        for(i=0; i<100; i++){
                A[i] = (rand()%1000); /*Set each element rndomly to 0-999 */
                if(A[i]>m){
			m = A[i];
		}
        }
	
	printf("Finding Max sequentially = %d\n", m);
	m = 0;
	#pragma omp parallel for reduction(max: m)
        for(i=0; i<100; i++){
		int tid = omp_get_thread_num();
                if(A[i] > m){
                  m = A[i];
                }
		printf("Thread num = %d, current maximum value = %d\n", tid, m);
        }
	printf("Find maximum value of A by using parallelism = %d\n", m);

}
