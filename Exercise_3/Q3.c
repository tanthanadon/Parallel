#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]){
	int A[100]; 
	int B[100];
	int C[100];
	int i, rank, size;
	srand(1234);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	
	if( rank == 0 ){
		for(i = 0; i < 100; i++){
			A[i] = i;
			B[i] = i*2;
		}
		printf("A[] and B[] are ready\n");
	}

	int chunkSize = ceil(100/size);
	int local_A[chunkSize];
	int local_B[chunkSize];
	int local_C[chunkSize];

	// Distribute chunkSize elements of an array A to all process
	MPI_Scatter(&A, chunkSize, MPI_INT, &local_A, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	// Distribute chunkSize elements of an array B to all process 
	MPI_Scatter(&B, chunkSize, MPI_INT, &local_B, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Scatter(&C, chunkSize, MPI_INT, &local_C, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

	for (i = 0; i < chunkSize; i++){
		local_C[i] = local_A[i] + local_B[i];
		//printf("%d + %d\n", local_A[i], local_B[i]); 
		//printf("local_C[%d] = %d\n", local_C[i]);
	}
	
	// Receive distinct part of C[] from all process with chunkSize elements
	MPI_Gather(&local_C, chunkSize, MPI_INT, &C, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	if( rank == 0){
		for( i = 0; i < 100; i++){	
			printf("%d\t", C[i]);
			if( (i%9) == 0){
				printf("\n");
			}
		}
	}	

	MPI_Finalize();
	return 0;
}
