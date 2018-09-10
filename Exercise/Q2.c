include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int i;
	int sum = 0;
  int m = 0;
  int A[100];
  srand(1234);    /* Set random seed */
  #pragma omp parallel for reduction(max: m)
  for(i=0; i<100; i++){
          A[i] = (rand()%1000); /*Set each element rndomly to 0-999 */
          sum += A[i];
          printf("%d\n", A[i]);
  }
   
	printf("%d\n", m);

}
