#include "immintrin.h"
#include <stdint.h>
#include <stdio.h>


float n = 2.0;
#define sqrt_n 1.41421356237f



#define A_00000(vector) \
    __asm__ ( \
        "vaddps %[v], %%ymm0, %%ymm0;" \
        : \
        : [v] "x" (vector) \
        : "ymm0", "ymm1" \
    );

#define A_00001(vector, i) \
    __asm__ ( \
        "vbroadcastss %[v], %%ymm1;" \
        : \
        : [v] "m" (vector[i]) \
        : "ymm1" \
    )

#define A_00002(arr) \
    __asm__ ( \
        "vmovaps %%ymm1, %[temp];" \
        : [temp] "=m" (arr) \
        : \
        : "ymm1" \
    )

__attribute__((__aligned__(32)))
static const float x_n[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};

/*taylor series values*/
__attribute__((__aligned__(32)))
static const float expansion[8] = {.3f, .2f, .14285714285f, .1f, .0909090909f, .07692307692f, .06f, .05882352941f};


/*Smothness of 1,620 -> 2^2 × 3^4 × 5*/
__attribute__((__aligned__(32)))
static const float fives[8] = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};


/*we are going to add a primality test to check for the smothness of the prime number*/
/*our alignment has to be pristine for this to work*/
inline p0X(__m256 a, __m256 b)
{


 A_00000(a);
 A_00001(b, 0);



}

void sieve() {

    __m256 x;
    __m256 taylor;
    __m256 smooth;
    __m256 log_approx;
    __m256 a_i;
    __m256 b_i;
    __m256i ones;

     x = _mm256_load_ps(x_n);
     taylor = _mm256_load_ps(expansion);


     ones = _mm256_set1_epi32(1);
     smooth = _mm256_load_ps(fives);


     log_approx = _mm256_div_ps(_mm256_sub_ps(x, _mm256_castsi256_ps(ones)), _mm256_add_ps(x, _mm256_castsi256_ps(ones)));
     taylor = _mm256_mul_ps(log_approx, taylor);

     a_i = _mm256_add_ps(x, _mm256_set1_ps(sqrt_n));
     b_i = _mm256_sub_ps(_mm256_mul_ps(a_i, a_i), _mm256_set1_ps(n));













}

int main() {
    sieve();
    return 0;
}
