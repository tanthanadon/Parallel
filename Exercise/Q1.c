#include <stdio.h>
#include <stdlib.h>

int main() {
	int A[100];
	int i = 0;
	srand(1234);
	/* Set random seed */

	for (i=0; i < 100; i++){

  		A[i] = (rand()%1000)*10;
 		printf("%d\n", A[i]);
	}

	/* Set each element randomly to 0-999 */

}
