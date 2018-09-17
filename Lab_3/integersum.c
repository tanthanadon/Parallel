#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Status status;
	int interval;
	int number, start, end, sum, GrandTotal;
	int proc;
	
	int LEFT, RIGHT;
	int arr[2];

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
	if (rank == 0) {
		printf("Enter LEFT: ");
		fflush(stdout);
		scanf("%d", &arr[0]);
		printf("Enter RIGHT: ");
		fflush(stdout);
		scanf("%d", &arr[1]);
		GrandTotal = 0;
	}	
	//Boardcast two elements of an array to another process
	MPI_Bcast(&arr, 2, MPI_INT, 0, MPI_COMM_WORLD);
	
		interval=(arr[1]-arr[0]+1)/(size-1);
		start=(rank)*interval+arr[0];
		end=start+interval-1;
		if (rank == (size-1)) {
			//For last block
			end = RIGHT;
		}
		//Sum locally on each proc
		sum = 0;
		for (number=start; number<=end; number++){
			sum = sum+number;
		}
		MPI_Reduce(&sum, &GrandTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		
		if(rank == 0){
			printf("GrandTotal = %d\n", GrandTotal);
		}
	
	MPI_Finalize();
}
