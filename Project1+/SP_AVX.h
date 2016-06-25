#pragma once
#include<immintrin.h>
const int count = 10000000;

inline void avx_256_processingSP(float data1[], float data2[])
{
	for (__m256* d1 = (__m256*)data1, *d2 = (__m256*)data2; d1 < (__m256*)(&data1[count - 1]);d1++, d2++)
	{
		__m256 results = _mm256_mul_ps(*d1, *d2);
		results = _mm256_add_ps(*d1, *d2);
		results = _mm256_div_ps(*d1, *d2);

	}
}
inline void avx_128_processingSP(float data1[], float data2[])
{
	for (__m128* d1 = (__m128*)data1, *d2 = (__m128*)data2; d1 < (__m128*)(&data1[count - 1]);d1++, d2++)
	{
		__m128 results = _mm_mul_ps(*d1, *d2);
		results = _mm_add_ps(*d1, *d2);
		results = _mm_div_ps(*d1, *d2);

	}
	
}
inline void no_avx_processingSP(float data1[], float data2[])
{
	for (int i = 0;i < count;i++)
	{
		float zwischen = data1[i] * data2[i];
		zwischen = data1[i] + data2[i];
		zwischen = data1[i] / data2[i];
	}
	
}