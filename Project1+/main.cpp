#include<iostream>
#include<chrono>
#include<ctime>
#include"SP_AVX.h"
#include"DP_AVX.h"



std::clock_t start;
void getTime(void(*pFunc)(double*, double*), double *a, double *b, char* type)
{
	start = std::clock();
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	pFunc(a, b);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
	std::cout << time_span.count() << " nanoseconds " << type << std::endl;
	std::cout << (std::clock() - start) << " cycles " << type << std::endl;

}
void getTime(void(*pFunc)(float[], float[]), float a[], float b[], char* type)
{
	start = std::clock();
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	pFunc(a, b);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
	std::cout << time_span.count() << " nanoseconds " << type << std::endl;
	std::cout << (std::clock() - start) << " cycles " << type << std::endl;

}


void doubleBench() 
{
	double *a;
	double *b;

	a = (double *)_aligned_malloc(count * sizeof(double),32);
	b = (double *)_aligned_malloc(count * sizeof(double), 32);

	for (int i = 0;i < count;i++)
	{
		a[i] = i*i*3.86856+1;
		b[i] = i*120.6945+2;
	}

	getTime(avx_256_processingDP, a, b, "AVX 256 bit DP");
	getTime(avx_128_processingDP, a, b, "AVX 128 bit DP");
	getTime(no_avx_processingDP, a, b, "No AVX DP");
	_aligned_free(a);
	_aligned_free(b);
}

void floatBench() 
{

	float *a;
	float *b;

	a = (float *)malloc(count * sizeof(float));
	b = (float *)malloc(count * sizeof(float));

	for (int i = 0;i < count;i++)
	{
		a[i] = i*i*3.86856f+1;
		b[i] = i*120.6945f+2;
	}
	getTime(avx_256_processingSP, a, b, "AVX 256 bit SP");
	getTime(avx_128_processingSP, a, b, "AVX 128 bit SP");
	getTime(no_avx_processingSP, a, b, "No AVX SP");
	free(a);
	free(b);

}


int main()
{
	//__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
	//__m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);
	//__m256 result = _mm256_add_ps(evens, odds);
	//float* f = (float*)&result;
	doubleBench();
	floatBench();
	std::getchar();
	return 0;
}