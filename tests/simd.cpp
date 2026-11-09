#include <immintrin.h>

typedef float f4 __attribute__((vector_size(16)));
typedef int i4 __attribute__((ext_vector_type(4)));

struct Holder {
  __m128 Lanes;
  f4 F;
};

f4 add(f4 a, f4 b) { return a + b; }

float dot(const float *a, const float *b) {
  __m128 x = _mm_loadu_ps(a);
  __m128 y = _mm_loadu_ps(b);
  __m128 m = _mm_mul_ps(x, y);
  float out[4];
  _mm_storeu_ps(out, m);
  return out[0] + out[1] + out[2] + out[3];
}

__attribute__((target("avx2"))) void avx(float *p) {
  __m256 v = _mm256_loadu_ps(p);
  _mm256_storeu_ps(p, v);
}

i4 shuffle(i4 v) { return __builtin_shufflevector(v, v, 3, 2, 1, 0); }

int plain(int x) { return x * 2; }
