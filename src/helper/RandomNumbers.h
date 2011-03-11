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
