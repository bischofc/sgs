
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
  static pair<double, double> getRandomNumberPair();
  static void sortGauss(vector<double>&);

public:
  static double getRandom();
  static int getRandom(int min, int max);
  static vector<double> getGaussianRandoms(unsigned int amount, double mean=0.0, float sd=1.0);
  virtual ~RandomNumbers();
};

}

#endif /* helper_randomNumbers_h */
