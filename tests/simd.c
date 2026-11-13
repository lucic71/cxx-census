#include <immintrin.h>

typedef float f4 __attribute__((vector_size(16)));

struct Holder {
  __m128 lanes;
  f4 f;
};

f4 add(f4 a, f4 b) { return a + b; }

float dot(const float *a, const float *b) {
  __m128 m = _mm_mul_ps(_mm_loadu_ps(a), _mm_loadu_ps(b));
  float out[4];
  _mm_storeu_ps(out, m);
  return out[0] + out[1] + out[2] + out[3];
}

int plain(int x) { return x * 2; }
