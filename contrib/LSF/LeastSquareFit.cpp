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

#include "LeastSquareFit.h"
#include <exception>

namespace helper {

/*
 * values is expected to be in the form of
 *    value[xValue] = yValue
 *    e.g. value at time 5 (hours) == value[5] = 12.34
 * degree is the maximal degree of the polynomial
 */
LeastSquareFit::LeastSquareFit(std::vector<int> values, int degree) : deg(degree) {
  // create and fill matrix
  Matrix mat (values.size(), deg+1);
  for(unsigned i = 0; i < values.size(); i++) {
    int j = deg;
    mat(i, j--) = 1.0;
    while(j >= 0) {
      mat(i, j) = mat(i, j+1) * i;
      j--;
    }
  }

  // create and fill vector
  Vector b (values.size());
  for(unsigned i = 0; i < values.size(); i++) {
    b(i) = values[i];
  }

  Vector z = mat.leastSquares(b);
  for(int i = deg; i >= 0; i--) {
    indices.push_back(z(i));
  }
}

int LeastSquareFit::operator[](int x) {
  //TODO check if indices.size() > 0
  int index = indices.size()-1;
  double tmp = indices[index--];
  while(index >= 0) {
    tmp = x * tmp + indices[index--];
  }
  return round(tmp);
}

void LeastSquareFit::printMatrix(Matrix mat)
{
  for (uint i = 0; i < mat.getNumberRows(); i++)
  {
    std::cout << "[ ";
    for (uint j = 0; j < mat.getNumberColumns(); j++)
    {
      std::cout << mat(i,j) << " ";
    }
    std::cout << "]" << std::endl;
  }
}

void LeastSquareFit::printVector(Vector vec)
{
  std::cout << "(";
  for (uint i = 0; i < vec.getSize()-1; i++)
    std::cout << vec(i) << ", ";
  std::cout << vec(vec.getSize()-1) << ")" << std::endl;
}


}
