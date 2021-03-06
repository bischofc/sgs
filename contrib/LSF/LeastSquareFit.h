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

#ifndef LEASTSQUAREFIT_H_
#define LEASTSQUAREFIT_H_

#include <vector>
#include "Matrix.h"

namespace helper {

class LeastSquareFit {
  std::vector<double> indices;
  const int deg;

private:
  void printMatrix(Matrix mat);
  void printVector(Vector vec);

public:
  LeastSquareFit(std::vector<int> values, int degree);
  int operator[](int index);
  virtual ~LeastSquareFit() {}
};

}

#endif /* LEASTSQUAREFIT_H_ */
