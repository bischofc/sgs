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

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>

namespace helper {

class Utils {
  Utils();

public:
  static std::vector<int> addIntVectors(std::vector<int>, std::vector<int>);
  virtual ~Utils();

public:
  template <class C>
  static std::vector<C> arrayToVector(C array[], int size) {
    std::vector<C> tmp;
    for(int i=0; i<size; i++) {
      tmp.push_back(array[i]);
    }
    return tmp;
  }

};

}

#endif /* UTILS_H_ */
