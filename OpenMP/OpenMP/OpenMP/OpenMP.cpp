#include <omp.h>
#include <stdio.h>
#include <Windows.h>


//Example 1
/*
int main(void)
{
#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		printf("hello (%d) ", ID);
		printf("world (%d)\n", ID);
		}
	system("pause");
	return 0;
}
*/

// Example 2 without OpenMP
/*
static long num_steps = 300000000;
double step;
int main(void)
{
	int i;
	double x, pi, sum = 0.0;
	DWORD start, end;

	step = 1.0 / (double)num_steps;

	start = GetTickCount();
	for (i = 0; i < num_steps; i++)
	{
		x = (i + 0.5)*step;
		sum = sum + 4.0 / (1.0 + x*x);
	}
	pi = step*sum;
	end = GetTickCount();
	printf("pi: %f \n", pi);
	printf("elapsed time: %f ms \n", (end - start)/1000.0);
	system("pause");
}
*/

// with OpenMP, set NUM_THREADS to 1, 2, 4 and measure time
/*
static long num_steps = 100000000;
double step;
#define NUM_THREADS 4

int main(void)
{
	int i, nthreads;
	double pi, sum[NUM_THREADS];
	step = 1.0 / (double)num_steps;

	DWORD start, end;
	start = GetTickCount();

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0)
			nthreads = nthrds;
		for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds)
		{
			x = (i + 0.5)*step;
			sum[id] += 4.0 / (1.0 + x*x);
		}
	}

	for (i = 0, pi = 0.0; i < nthreads; i++)
		pi += sum[i] * step;
	end = GetTickCount();
	printf("pi: %f \n", pi);
	printf("elapsed time: %f ms \n", (end - start) / 1000.0);
	system("pause");
}
*/

// OpenMP parallel for with reduction
/*
static long num_steps = 100000000;
double step;

int main(void)
{
	int i;
	double pi, sum = 0.0;
	step = 1.0 / (double)num_steps;

	DWORD start, end;
	start = GetTickCount();

	#pragma omp parallel
	{
		double x;
		#pragma omp for reduction(+:sum)
		for (i = 0; i < num_steps; i++)
		{
			x = (i + 0.5)*step;
			sum = sum + 4.0 / (1.0 + x*x);
		}
	}

	pi = step * sum;
	end = GetTickCount();
	printf("pi: %f \n", pi);
	printf("elapsed time: %f ms \n", (end - start) / 1000.0);
	system("pause");
}
*/