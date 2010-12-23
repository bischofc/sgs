
#ifndef helper_randomNumbers_h
#define helper_randomNumbers_h

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

namespace helper {

class RandomNumbers {
  static int initValue;

  RandomNumbers();
  static void initialize();
  static float getRandom();
  static pair<float, float> getRandomNumberPair();
  static void sortGauss(vector<float>&);

public:
  static vector<float> getGaussianRandoms(unsigned int amount, float mean=0.0, float sd=1.0);
  virtual ~RandomNumbers() {};
};

}

#endif /* helper_randomNumbers_h */
