# CS430-Parallel-Programming-
Assignment for CS430 Parallel Programming ( Monsoon 2016 )


	clock_t start, end;
	double cpu_time_used;

	start = clock();

	/* parallization code */

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


