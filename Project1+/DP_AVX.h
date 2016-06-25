#pragma once
#include<immintrin.h>

inline void avx_256_processingDP(double* data1, double* data2)
{
	for (__m256d* d1 = (__m256d*)data1, *d2 = (__m256d*)data2; d1 < (__m256d*)(&data1[count - 1]);d1++,d2++)
	{
		__m256d results = _mm256_mul_pd(*d1, *d2);
		results = _mm256_add_pd(*d1, *d2);
		results = _mm256_div_pd(*d1, *d2);
		
	}
	
}
inline void avx_128_processingDP(double *data1, double *data2)
{
	for (__m128d* d1 = (__m128d*)data1, *d2 = (__m128d*)data2; d1 < (__m128d*)(&data1[count - 1]);d1++, d2++)
	{
		__m128d results = _mm_mul_pd(*d1, *d2);
		results = _mm_add_pd(*d1, *d2);
		results = _mm_div_pd(*d1, *d2);

	}
}
inline void no_avx_processingDP(double *data1, double *data2)
{

	for (int i = 0;i < count;i++)
	{
		double zwischen = data1[i] * data2[i];
		zwischen = data1[i] + data2[i];
		zwischen = data1[i] / data2[i];
	}

}