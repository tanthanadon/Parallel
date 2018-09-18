#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[]){
	
	int rank, size;
	int i, j;
	int arr[8][8];
	int temp[8];
	int msgtag = 1234;
	
	int sum, GrandTotal;

	MPI_Init(&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Status status;
	
	// The number of all processors is 9;
	// Master 1 slav processor 8
	if (rank == 0){
		// Initialize an array
		for ( i = 0; i < 8; i++ ){
			for (j = 0; j < 8; j++){
				arr[i][j] = i+j;
			}
		}
		
		for ( i = 1; i <= 8; i++ ){
			MPI_Send(&arr[i-1][0], 8, MPI_INT, i, msgtag, MPI_COMM_WORLD);
			printf("Processor %d sent arr[%d][0] to Processor %d\n", rank, i-1, i);
		}
		
		GrandTotal = 0;
		for( i = 1; i < size; i++ ){
			MPI_Recv(&sum, 1, MPI_INT, i, msgtag, MPI_COMM_WORLD, &status);
			GrandTotal += sum;
		}
		
		printf("Grand total = %d\n", GrandTotal);
	}
	else{
		MPI_Recv(&temp, 8, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
		printf("Processor %d recevied\n", rank);
		sum = 0;
		for ( i = 0; i < 8; i++){
			sum += temp[i];			
		}	
		
		printf("Process %d: Sum = %d\n", rank, sum);
		// Send the summation of each row of an array to processor 0
		MPI_Send(&sum, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();

}
