#include "immintrin.h"
#include <stdint.h>
#include <stdio.h>




#define PRINT(vector) \
    do { \
        for (int i = 0; i < 8; i++) { \
            printf("\n%f --> %f \n", vector[i], (float)i); \
        } \
    } while (0)


#define idx(v, i) ({\
     __m256 vt = _mm256_permute2f128_ps(v, v, (i >> 2) | ((i >> 2) << 4)); \
     vt = _mm256_permute_ps(vt, _MM_SHUFFLE(i & 3, i & 3, i & 3, i & 3)); \
})





/*these residues will be used for later*/
typedef struct residue_narrow {
  __attribute__((__aligned__(16)))
  int32_t limbs[8];
} residue_narrow_t;


/*taylor expansion */

/*I dont think we can do residue like x^2 = q mod n or x ^*/



float n  = 2.0f;
float sqrt_n =  1.41421356237f;


__attribute__((__aligned__(32)))
static const float x_n[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};

/*taylor series values*/
__attribute__((__aligned__(32)))
static const float expansion[8] = {0.0f, .3f, .2f, .14285714285f, .1f, .0909090909f, .07692307692f, .06f};



/*Smothness of 1,620 -> 2^2 × 3^4 × 5*/
__attribute__((__aligned__(32)))
static const float fives[8] = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};


/*got this on stack exchange broadcast x values then it should be x^1, x^2 ... s on*/
__m256 _mm256_powers_ps(float x) {
    float const x2 = x * x, x4 = x2 * x2;
    return _mm256_mul_ps(
        _mm256_mul_ps(
            _mm256_setr_ps( x, x2,  x, x2,  x, x2,  x, x2),
            _mm256_setr_ps( 1,  1, x2, x2,  1,  1, x2, x2)
        ),
            _mm256_setr_ps( 1,  1,  1,  1, x4, x4, x4, x4)
    );
}


/*we are going to add a primality test to check for the smothness of the prime number*/
/*our alignment has to be pristine for this to work*/
void sieve() {

    __m256 x;

   /*vectors taht will be used in */
    __m256 taylor;
    __m256 smooth;

    __m256 a_i;
    __m256 b_i;

    __m256 ones;
    __m256 scalar;
    __m256 log;
    float temp[8];




     x = _mm256_load_ps(x_n);
     taylor = _mm256_load_ps(expansion);


     ones = _mm256_set1_ps(1.0f);
     smooth = _mm256_load_ps(fives);

    /*they already implemented the log function*/

     log = _mm256_div_ps(_mm256_sub_ps(x, ones), _mm256_add_ps(x, ones));



     /*this is taylor series of a log function*/

     log = _mm256_mul_ps(log, taylor);

     _mm256 scalar = _mm256_loadu_ps(&log[0]);
     PRINT(log);


     a_i = _mm256_add_ps(x, _mm256_set1_ps(sqrt_n));
     b_i = _mm256_sub_ps(_mm256_mul_ps(a_i, a_i), _mm256_set1_ps(n));

     /*this sort of works like a broadcast*/

     PRINT(b_i);


     for(int i = 0; i < 8; i++)
     {

    // log =  _mm256_powers_ps(i);

     }
     PRINT(log);











}

int main() {
    sieve();
    return 0;
}
