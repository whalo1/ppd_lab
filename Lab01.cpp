#include "pch.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <time.h>
using namespace std;




int main()
{
	int N = 1000;
	int M = 1000;

	int *b;
	b = new int[N];

	int *A;
	A = new int[N*M];

	int *vector;
	vector = new int[N];

	for (int i = 0; i < N; i++)
	{
		b[i] = rand() % 100;
		for (int j = 0; j < M; j++)
		{
			A[i*N+j] = rand() % 100;
		}
	}


	//CLOCK
	clock_t start, end;
	start = clock();

	// Print Vector
#pragma omp parallel for
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			vector[i] += b[j] * A[i*N + j];
		}
	}


	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";

	return 0;
}