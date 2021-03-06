#include <iostream>
#include <cstdlib>
#include <cassert>

template<typename T = float>
inline T lerp(const T &lo, const T &hi, const T &t)
{ return lo * (1 - t) + hi * t; }

class ValueNoise1D {
public:
  ValueNoise1D (unsigned seed = 2011){
    srand48(seed);
    for (unsigned i = 0; i < kMaxVertices; i++) {
      r[i] = drand48();
    }
  }

  // Evaluate the noise function at position x
  float eval(const float &x){
    int xi = (int)x - (x < 0 && x != (int)x);
    int xMin = xi % kMaxVerticesMask;
    float t = x - xi;
    int xMax = (xMin+1) % kMaxVerticesMask;

    return lerp(r[xMin], r[xMax], t);
  }
  
  

  static const unsigned kMaxVertices = 10;
  static const unsigned kMaxVerticesMask = kMaxVertices - 1;
  float r[kMaxVertices];
};

int main(int argc, char const *argv[]) {
  ValueNoise1D valueNoise1D;
  
  for (int i = -2000; i <= 2000; i++) {
    float x = 0.01 * i;
    std::cout << x << ", " << valueNoise1D.eval(x) << std::endl;
  }

  return 0;
}
