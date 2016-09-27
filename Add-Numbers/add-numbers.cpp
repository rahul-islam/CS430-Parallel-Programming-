#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

	//Generate 100 random numbers

	int arr[100];
	srand (time(NULL));
	for(int i=0; i<100; i++) {
		arr[i]=rand() % 100 + 1;
	}

	int t_sum_1=0,t_sum_2=0; //temp sum container

	clock_t start, end;
	double cpu_time_used;

	start = clock(); //start clock
 	#pragma omp parallel num_threads(2)
	{
		int id = omp_get_thread_num();
		// divide work among 2 thread available
		if(id==0) 	// assign work for first thread
			for (int i=0;i<100;i=i+2)
				t_sum_1 = t_sum_1+arr[i];
		else		// assign work for second thread
			for (int i=1;i<100;i=i+2)
				t_sum_1 = t_sum_1+arr[i];
	}

	end = clock(); //stop clock
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // calc time difference 
	
	// grand total of sums by two thread
	int sum  = t_sum_1+t_sum_2;
	printf("Total = %d\n",sum);

	printf("\n%lf time enlapsed \n",cpu_time_used);

	return 0;
}
