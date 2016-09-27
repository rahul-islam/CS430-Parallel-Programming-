#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int arr[10][10];
	
	// Generate a Random matrix of 10 x 10
	srand (time(NULL));
	printf("\nMATRIX\n");
	for(int i=0;i<10; i++) {
		for(int j=0; j<10; j++) {
			arr[i][j]= rand() % 10 + 1;;
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}

	clock_t start, end;
	double cpu_time_used;

	start = clock(); // clock starts
	#pragma omp parallel num_threads(2) // two threads are created
	{
		int id = omp_get_thread_num();
		int tmp = 0;
		// now divide work between 2 threads available
		if(id==0){	//work for thread 1
			// tranpose code
			for (int i=0;i<10;i=i+2) {
				for(int j=i;j<10;j++) {
					tmp = arr[i][j];
					arr[i][j] = arr[j][i];
					arr[j][i] = tmp;
				}
			}
		}
		else {		// work for thread 2
			// tranpose code
			for (int i=1;i<10;i=i+2) {
				for(int j=i;j<10;j++) {
					tmp = arr[i][j];
					arr[i][j] = arr[j][i];
					arr[j][i] = tmp;
				}
			}
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTRANSPOSE MATRIX\n");
	for(int i=0;i<10; i++) {
		for(int j=0; j<10; j++) {
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n%lf time enlapsed\n",cpu_time_used);

}
