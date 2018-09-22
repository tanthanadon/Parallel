#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

void seq(int arr[]){
	int i, max, min, sum;
	double avr;

	max = arr[0];
	min = arr[0];
	sum = 0;

	for ( i = 0; i < 100; i++){
		if ( arr[i] > max ){
			max = arr[i];
		}

		if ( arr[i] < min ){
			min = arr[i];
		}
		
		sum += arr[i];
	}
	
	avr = sum / 100;
	printf("========Sequential version========\n");
	printf("Max = %d, Min = %d, Sum = %d, Average = %f\n", max, min, sum, avr);
	printf("==================================\n");

}

int main (int argc, char* argv[]){
	int A[100];
	int i;
	srand(1234); // Set the range of randomed number
	
	int global_max;
	int global_min;
	int global_sum;
	double avr;

	int rank, size;
	
	for ( i = 0; i < 100; i++){
		A[i] = rand()%1000;
	}
	
	MPI_Init ( &argc, &argv);
	MPI_Comm_rank ( MPI_COMM_WORLD, &rank);
	MPI_Comm_size ( MPI_COMM_WORLD, &size);

	int chunkSize = ceil(100 / size);
	int local_arr[chunkSize];

	MPI_Scatter( &A, chunkSize, MPI_INT, &local_arr, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

	int local_max = local_arr[0];
	int local_min = local_arr[0];
	int local_sum = 0;

	printf("Rank %d received\n", rank);
	for ( i = 0; i < chunkSize; i++){

		if( local_arr[i] > local_max){
			local_max = local_arr[i];
		}

		if( local_arr[i] < local_min){
			local_min = local_arr[i];
		}

		local_sum += local_arr[i];
	}
	
	MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if( rank == 0){
		avr = global_sum / 100;
		seq(A);
		printf("Global: Max = %d, Min = %d, Sum = %d, Average = %f\n", global_max, global_min, global_sum, avr);
	}

	MPI_Finalize();


}
