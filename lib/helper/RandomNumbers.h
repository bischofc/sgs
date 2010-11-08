
#ifndef RANDOMNUMBERS_H_
#define RANDOMNUMBERS_H_

#include <vector>
using namespace std;

namespace helper {

class RandomNumbers {
  static int initValue;

  RandomNumbers();
  static void initialize();
  static float getRandom();
  static pair<float, float> getRandomNumberPair();

public:
  static vector<float> getGaussianRandoms(unsigned int amount, float mean=0.0, float sd=1.0);
  virtual ~RandomNumbers() {};
};

}

#endif /* RANDOMNUMBERS_H_ */
