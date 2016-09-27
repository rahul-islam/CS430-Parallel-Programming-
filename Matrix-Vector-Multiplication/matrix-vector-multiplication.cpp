#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int marr[10][10], varr[10], rarr[10];
	srand (time(NULL));
	prinf("\nMatrix\n")
	//random matrix and vector generate
	for(int i=0;i<10; i++){
		for(int j=0; j<10; j++){
			marr[i][j]=rand() % 10 + 1;
			printf("%d\t",marr[i][j]);
		}
		printf("\n");
		varr[i]=rand() % 10 + 1;
	}
	prinf("\nVector\n")
	//
	for(int i=0; i<10; i++){
		printf("%d\t",varr[i]);
	}

	clock_t start, end;
	double cpu_time_used;

	start = clock();
	#pragma omp parallel num_threads(2)
	{
		int id = omp_get_thread_num();
		int sum=0;
		for(int i=id;i<10;i=i+2){
			sum=0;
			#pragma omp parallel num_threads(2)
			{
				// matrix-row X vector-col
				for(int j=0;j<10;j++){
					printf("%d\t",omp_get_thread_num());
					sum=marr[i][j]*varr[j]+sum;
				}
			}

			rarr[i]=sum; // result of matrix-row X vector-col
		}
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	for(int i=0;i<10;i++){
		printf("%d\t",rarr[i]);
	}

	printf("\n%lf time enlapsed \n",cpu_time_used);

	return 0;
}
