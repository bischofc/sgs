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

#include "Utils.h"

namespace helper {

std::vector<int> Utils::addIntVectors(std::vector<int> a, std::vector<int> b) {
  std::vector<int> tmp;
  unsigned s = a.size() < b.size() ? b.size() : a.size();
  for(unsigned i = 0; i < s; i++) {
    int x = a.size() > i ? a.at(i) : 0;
    int y = b.size() > i ? b.at(i) : 0;
    tmp.push_back(x+y);
  }
  return tmp;
}

}
