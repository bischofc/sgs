/*
Copyright (C) 2010 Christian Bischof (bischof.christian@gmail.com)
This file is part of "Smart Grid Simulator".

"Smart Grid Simulator" is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Smart Grid Simulator" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Smart Grid Simulator".  If not, see <http://www.gnu.org/licenses/>.
*/

#include "RandomNumbers.h"

namespace helper {

int RandomNumbers::initValue;

void RandomNumbers::initialize() {
  initValue = time( NULL );
  srand(initValue);
}

// [0.00 : 1.00]
double RandomNumbers::getRandom() {
  if(initValue == 0) initialize();
  return (rand() % 101) / 100.0;
}

// [min : max]
int RandomNumbers::getRandom(int min, int max) {
  if(initValue == 0) initialize();
  return (rand() % (max-min+1)) + min;
}

pair<double, double> RandomNumbers::getRandomNumberPair() {
  pair<double, double> retVal (getRandom(), getRandom());
  return retVal;
}

vector<double> RandomNumbers::getGaussianRandoms(unsigned int amount, double mean, float sd) {
  vector<double> retVal;
  do {
    double newVal;
    pair<double, double> pair = getRandomNumberPair();

    double x = -log(pair.first);
    double y = exp((x-1)*(x-1)/-2);

    if(pair.second > y) continue;

    if(getRandom() > 0.5) {
      newVal = mean+sd*x;
    } else {
      newVal = mean-sd*x;
    }

    retVal.push_back(newVal);
  } while(retVal.size() < amount);
  sortGauss(retVal);
  return retVal;
}

void RandomNumbers::sortGauss(vector<double> & vec) {
  vector<double> tmp;
  vector<double>::iterator it;
  bool direction = true;
  sort(vec.begin(), vec.end());

  for(it=vec.end()-1; it!=vec.begin()-1; it--) {
    if(direction) tmp.insert(tmp.begin(), *it);
    else tmp.insert(tmp.end(), *it);
    direction = !direction;
  }

  vec.swap(tmp);
}

}
