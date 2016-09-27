#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main()
{
        int arr[10], temp[10];
	srand (time(NULL));
        // fill arr[] with random numbers
	printf("\nArray\n");
        for (int i = 0; i < 10; i++) {
            arr[i] = rand() % 10 + 1;
	    printf("%d\t",arr[i] );
        }

	int flag=1;
        temp[0] = arr[0]; //first element 


        omp_set_num_threads(2);
        int num_threads = omp_get_num_threads();

	clock_t start, end;
	double cpu_time_used;

	start = clock(); //start clock
        while (flag<10) {

            #pragma omp parallel private(i)
            {
                int id = omp_get_thread_num();
                for (int i = id; i+flag < 10; i+=num_threads) {
                    temp[i+flag] = arr[i] + arr [i+flag];
                }
            }
            #pragma omp parallel for
                for (int i = 0; i < 10; i++) {
                    arr[i] = temp[i];
                }

            flag = flag*2;
        }

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("\nPrefix Sum \n");
        for (int i = 0; i < 10; i++) {
            printf("%d\t",arr[i] );
        }

	printf("\n%lf time enlapsed \n",cpu_time_used);

	return 0;
}
