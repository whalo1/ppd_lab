// Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    //Alocare de memorie pentru imagine
	int imgSize = 10000;
	unsigned char *img = new unsigned char[imgSize*imgSize];

	int nr_ch = 4;
	int ch_size = 2500;
	int **h_group = new int *[nr_ch];

	//alocare memoriei pt histograma
	for (int i = 0; i < nr_ch; i++)
	{
		h_group[i] = new int[256];
		for (int j = 0; j < 256; j++)
		{
			h_group[i][j] = 0;
		}
	}

	//initializarea imaginii
	for (int i = 0; i < imgSize; i++)
	{
		for (int j = 0; j < imgSize; j++)
		{
			img[i*imgSize + j] = i % 256;
		}
	}


	clock_t start = clock();
#pragma omp parallel for
	for (int i = 0; i < nr_ch; i++)
	{
		int startIndex = i * ch_size;
		int stopIndex = (i + 1)*ch_size;
		//calculul histogramei
		for (int j = startIndex; j < stopIndex; j++)
		{
			for (int r = 0; r < imgSize; r++)
			{
				h_group[i][img[j * imgSize + j]]++;
			}
		}
	}

	clock_t end = clock();

	int *histograma = new int[256];
	for (int i = 0; i < 256; i++)
	{
		histograma[i] = 0;

	}

	for (int i = 0; i < nr_ch; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			histograma[j] += h_group[i][j];

		}
	}

	//afisarea histogramei
	for (int i = 0; i < 256; i++)
	{
		cout << histograma[i] << " ";
	}

	cout << endl;

	//Afisarea timpului de executie
	cout << "time: " << double(end - start) / CLOCKS_PER_SEC << endl;

	//Dealocare memoriei
	delete[] img;
	for (int i = 0; i < nr_ch; i++)
	{
		delete[] h_group[i];
	}

	delete[] histograma;
	delete[] h_group;



	return 0;
}