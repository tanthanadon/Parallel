#include <mpi.h>
#include <stdio.h>

#define LEFT 1
#define RIGHT 1000

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Status status;
	int interval;
	int number, start, end, sum, GrandTotal;
	int proc;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
	if (rank == 0) {
		GrandTotal = 0;
		for (proc=1; proc<size; proc++) {
			MPI_Recv(&sum,1,MPI_INT,proc,123,MPI_COMM_WORLD, &status);
			GrandTotal=GrandTotal+sum;
		}
		printf("Grand total = %d\n", GrandTotal);
	}
	else {
		interval=(RIGHT-LEFT+1)/(size-1);
		start=(rank-1)*interval+LEFT;
		end=start+interval-1;
		if (rank == (size-1)) {
			//For last block
			end = RIGHT;
		}
		//Sum locally on each proc
		sum = 0;
		for (number=start; number<=end; number++)
			sum = sum+number;
		
		printf("Rank %d: start %d, end %d, local sum %d\n", rank,  start, end, sum);
		//Send local sum to Master process
		MPI_Send(&sum,1,MPI_INT,0,123,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
