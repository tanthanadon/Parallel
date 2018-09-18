#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[]){
	
	int size, rank, i;
	
	MPI_Init( &argc, &argv);
	MPI_Status status;	
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	int msgtag = 1234;

	int arr[10];
	
	if (rank == 0) {
		// Initialize integers in an array
		for(i = 0; i < 10; i++){
			arr[i] = i;
		}
		
		MPI_Send(arr, 10, MPI_INT, 1, msgtag, MPI_COMM_WORLD); 
		printf("Processor %d sent an array!\n", rank);
		
		MPI_Recv(arr, 10, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
		printf("Processor %d received an array\n", rank);
		
		for(i = 0; i < 10; i++){
			printf("arr[%d] = %d\n", i, arr[i]);
		}
	}
	
	else if (rank == 1){
		// Processor 1 received 10 integers in an array from processor 0
		MPI_Recv(arr, 10, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
		printf("Processor %d received an array!\n", rank);
		
		for(i = 0; i < 10; i++){
			arr[i] = arr[i]*10;
		}
		
		// Processor 1 sent 10 integers as an array to processor 0 
		MPI_Send(arr, 10, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
		printf("Processor %d sent a new array\n", rank);
	}
	
	MPI_Finalize();


}
