#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
	int rank; // Process rank
	int size; // Number of processes
	int msgtag; //Message tag
	MPI_Status status;
	
	int x; // Base	
	int square; // Result of square
	
	MPI_Init( &argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	
	msgtag = 1234;
	if(rank == 0){
		x = 3;
		MPI_Send(&x, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
		// Send a value of int x to processsor 1
		printf("processor %d sent %d\n", rank, x);
		MPI_Recv(&square, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
		// Receive square value from processor 1 
		printf("Processor %d received\n", rank);
		printf("Square of %d = %d\n", x, square);
	}
	else{
		MPI_Recv(&x, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
		// Receive a value of int x from processor 0 with extra information e.g. error status,  message tag, and sender rank
		printf("Processor %d received = %d\n", rank, x);
		square = x*x;
		MPI_Send(&square, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
		printf("Processor %d sent = %d\n", rank, square);
	}
	MPI_Finalize();
		
}
