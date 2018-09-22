#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define N 8
int main (int argc, char* argv[]){
	int A[N][N];
	int i, j;
	int sum;
	int total;
	srand(1234); // Set the range of randomed number

	int global_sum[N];
	int rank, size;
	
	MPI_Init ( &argc, &argv);
	MPI_Comm_rank ( MPI_COMM_WORLD, &rank);
	MPI_Comm_size ( MPI_COMM_WORLD, &size);

	if( rank == 0){
		printf("=====Sequential version=====\n");
		for( i = 0; i < N; i++){
			for( j = 0; j < N; j++){
				A[i][j] = rand()%1000;
				//printf("%d ", A[i][j]);
				sum += A[i][j];
			}

		}
		printf("Sum = %d\n", sum);
		printf("=============================\n");
	}

	int chunkSize = ceil(N/size);
	int local_arr[N][N];
	int local_sum[N];
	//printf("%d\n", chunkSize);
	
	// Distribute N*chunkSize elements of an array A as a block of rows to each task
	MPI_Scatter(&A, N*chunkSize, MPI_INT, &local_arr, N*chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	// Row 1 8*2 = 16 elements which seperate to be two parts for 4 processors

	//printf("Rank %d received\n", rank);
	// Sum N*chunkSize elements for each process
	// Row 0 -> Process 0 N*chunkSize elements
	// Row 1 -> Process 1 N*chunkSize elements
	// Row 2 -> Process 2 N*chunkSize elements
	// Therefore, local_sum[0] keeps the summation of Row 0
	// local_sum[1] keeps the suumation of Row 1
	for( i = 0; i < chunkSize; i++){
		local_sum[i] = 0;
		for( j = 0; j < N; j++){
			//printf("local_arr[%d][%d] = %d\n", i, j, local_arr[i][j]);
			local_sum[i] += local_arr[i][j];
		}
		printf("Rand %d: local_sum[%d] = %d\n", rank, i, local_sum[i]);
	}
	
	// Send chunkSize elments that is the sammation of each rank back to global_sum chunkSize elements in master process
	MPI_Gather(&local_sum, chunkSize, MPI_INT, &global_sum, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	if( rank == 0){
		total = 0;
		for( i = 0; i < N; i++){
			//printf("Global: Sum = %d\n", global_sum[i]);
			total += global_sum[i];
		}
		printf("Total = %d\n", total);
	}

	MPI_Finalize();
	
	return 0;
}
