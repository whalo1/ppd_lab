// Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <time.h>

using namespace std;

float random_number(float a, float b)
{
	float r = rand() / RAND_MAX;
	float diff = (float)(b - a);
	float p = r * diff;
	return a + p;
}

int main()
{
	int a = -1;
	int b = 1;
	int nCerc, nTotal;
	float x, y, distance, pi;
	nTotal = 100000;
	nCerc = 0;

	omp_set_num_threads(4);

	clock_t start, end;
	start = clock();

#pragma omp parallel
	{	
		int id = omp_get_thread_num();
		int nThreads = omp_get_num_threads();
		int istart = id * nTotal / nThreads;
		int iend = (id + 1) * nTotal / nThreads;
		for (int i = istart; i < iend; i++)
		{
			x = a + (b - a) * ((float)rand()) / (float)RAND_MAX;
			y = a + (float)(b - a) * ((float)rand()) / (float)RAND_MAX;

			distance = sqrt((x - 0.0)*(x - 0.0) + (y - 0)*(y - 0));
			if (distance < 1)
			{
				nCerc += 1;
			}
		}
	}
	pi =(float)4 * nCerc / nTotal;
	end = clock();
	cout << "time:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

	cout << nCerc << endl;
	cout << pi;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
