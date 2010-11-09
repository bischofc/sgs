#include <RandomNumbers.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

namespace helper {

int RandomNumbers::initValue;

void RandomNumbers::initialize() {
  initValue = time( NULL );
}

float RandomNumbers::getRandom() {
  return (rand() % 101) / 100.0;
}

pair<float, float> RandomNumbers::getRandomNumberPair() {
  if(initValue == 0) initialize();
  pair<float, float> retVal (getRandom(), getRandom());
  return retVal;
}

vector<float> RandomNumbers::getGaussianRandoms(unsigned int amount, float mean, float sd) {
  vector<float> retVal;
  do {
    float newVal;
    pair<float, float> pair = getRandomNumberPair();

    float y = exp((-(pair.second-1)*(pair.second-1))/2);
    if(pair.second > y) continue;

    float x = log(pair.first);
    if(getRandom() < 0.5) {
      newVal = mean+sd*x;
    } else {
      newVal = mean-sd*x;
    }

    retVal.push_back(newVal);
  } while(retVal.size() < amount);
  return retVal;
}

}
