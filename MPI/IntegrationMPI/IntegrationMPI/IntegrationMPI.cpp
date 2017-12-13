/************************************
Computer Engineering
Homework MPI - OpenMP

Author: Kael Ricardo Kill
************************************/

/*
	Open CMD on the folder .\IntegrationMPI\Debug, run with:
	mpiexec -n (numberOfProcess) 'ProjectName'
*/

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <Windows.h>
#include <mpi.h>

double Integration(double start, double end, double(*IntegralFunction) (double), int div);

double IntegralFunction(double x)
{
	return x * x * x + 2 * sin(x) + 5 * x;
}

int rank, num;

int main(int arg, char* argv[])
{
	MPI_Init(&arg, &argv);
	
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num);
	
	double start, end, fres;
	int div;

	DWORD tickStart, tickEnd;
	fres = 0;
	start = 0;
	end = 50;
	//start = rank * 50. / num;
	//end = (rank + 1) * 50. / num;
	div = 100000000 /num;

	if (rank == 0) {
		
		tickStart = GetTickCount();
		double res = Integration(start, end, IntegralFunction, div);
		//printf("proc: %d start %f end %f res = %f\n", rank, start, end, res);
		MPI_Reduce(&res, &fres, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		tickEnd = GetTickCount();
		printf("Result: %f\n", fres);
		printf("Elapse time: %d\n", tickEnd - tickStart);
	}
	else {
		
		double res = Integration(start, end, IntegralFunction, div);
		//printf("proc: %d start %f end %f res = %f\n", rank, start, end, res);
		MPI_Reduce(&res, &fres, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		
	}
	MPI_Finalize();
	return(0);
}

double Integration(double start, double end, double(*f) (double), int div)
{
	
	double x = start;
	double step = (end - start) / div;
	double A = start;
	int i;
	
#pragma omp parallel for reduction(+:A) 
	for (i = 1; i < div; i+=num)
	{
		A += f(i*step);
	}
	return A* step;
}


