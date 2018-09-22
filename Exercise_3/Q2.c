#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


int main (int argc, char* argv[]){
	int A[100];
	int i;
	srand(1234); // Set the range of randomed number
	int x;
	
	int rank, size;
	
	int global_count;
	
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	if( rank == 0){
		for ( i = 0; i < 100; i++){
			A[i] = rand()%1000;
		}
	
		// Get an integer from the user
		printf("Enter an integer: \n");
		scanf("%d", &x);
	 	fflush(stdin);
	}

	int chunkSize = ceil(100 / size);
	int local_arr[chunkSize];

	// Distribute distinct part of the array to all process
	MPI_Scatter( &A, chunkSize, MPI_INT, &local_arr, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	// Boardcast integer x to all process
	MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	int local_count = 0;

	for ( i = 0; i < chunkSize; i++){

		if( local_arr[i] < x){
			local_count++;
		}
	}
	
	printf("Rank %d: Count = %d\n", rank, local_count);
	MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if( rank == 0){
		printf("===== Global: Count = %d =====\n", global_count);
	}

	MPI_Finalize();


}
