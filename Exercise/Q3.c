int main(){
	int i;
	int sum = 0;
        int m = 0;
        int A[100];
        srand(1234);    /* Set random seed */
        for(i=0; i<100; i++){
                A[i] = (rand()%1000); /*Set each element rndomly to 0-999 */
                printf("%d\n", A[i]);
        }

	#pragma omp parallel for reduction(max: m)
        for(i=0; i<100; i++){
                printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
                if(A[i] >= 500){
                  m = A[i];
                }
        }
	printf("%d\n", m);

}
