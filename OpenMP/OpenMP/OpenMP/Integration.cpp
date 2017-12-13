#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <Windows.h>

double Integration(double start, double end, double(*IntegralFunction) (double), int div);

double IntegralFunction(double x)
{
	return x * x * x + 2 * sin(x) + 5 * x;
}

int main()
{
	double start, end;
	int div;

	DWORD tickStart, tickEnd;

	start = 0;
	end = 50;
	div = 100000000;
	tickStart = GetTickCount();
	double res = Integration(start, end, IntegralFunction, div);
	tickEnd = GetTickCount();
	printf("Result: %f\n", res);
	printf("Elapse time: %d\n", tickEnd - tickStart);
	system("pause");
	return(0);
}

double Integration(double start, double end, double(*f) (double), int div)
{
	double A = 0;
	double x = start;
	double step = (end - start) / div;
	
#pragma omp parallel for reduction(+:A) 
	for (int i = 1; i < div; i++)
	{
		//x += step;
		A += f((i)*step);
	}
	return A* step;
}


// 7125  1568750.032609
// 3542
// 2235	 1568750.038756