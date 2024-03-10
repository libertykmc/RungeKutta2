#include <iostream>
#include <math.h>
#include <Windows.h>
#include <omp.h>

const int n = 2;
const double t0 = 0.0;
const double tmax = 10.0;
double t = t0;
const double tau = 0.001;
double y[n] = { 0.0, 0.125 };
double yy[n] = { 0.0,0.0 };
double ff[n] = { 0.0, 0.0 };

double f(double* y, double x, int i)
{
	double w= 0;

	switch (i)
	{
	case 0: w = y[1];
		break;

	case 1: w = -0.07 * x * y[1] - x * x * y[0];
		break;
	}

	return w;
}

int main()
{
	double time_begin, time_end, delta;

	time_begin = omp_get_wtime();

	for (double t = t0; t <= tmax; t += tau)
	{
		for (int i = 0; i < n; i++)
	{
			yy[i] = y[i] + 0.5 * tau * f(y, t, i);
		}
		for (int i = 0; i < n; i++)
		{
			y[i] += tau * f(yy, t + tau * 0.5, i);
		}
	}

	time_end = omp_get_wtime();

	delta = time_end - time_begin;

	std::cout << "time = " << delta << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << "y[" << i << "] " << y[i] << std::endl;
	}

	system("pause");

}
//Метод Рунге-Кутта 2