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

#include "BasicStrategy.h"
#include <iostream>//TODO

namespace simulation {
namespace endpoint {
namespace consumer {

std::multimap<int, int> BasicStrategy::getMoves(const std::vector<int> &adjustment) {
  std::multimap<int, int> tmp;
  std::multimap<int, int, largeToSmallComperator> overplus;
  std::multimap<int, int, largeToSmallComperator>::iterator ito;
  std::multimap<int, int> deficit;
  std::multimap<int, int>::iterator itd;

  for(unsigned i=0; i < adjustment.size(); i++) {
    int v = adjustment.at(i);
    if(v > 0) {
      std::pair<int, int> p (v, i);
      overplus.insert(p);
    } else if(v < 0){
      std::pair<int, int> p (v, i);
      deficit.insert(p);
    }
  }

  // TODO improve algorithm (very basic, does not regard many things including already moved energy plans)
  for(ito = overplus.begin(); ito != overplus.end(); ito++) {
    int currOp = ito->first;
    for(itd = deficit.begin(); itd != deficit.end(); itd++) {
      if(itd->first > currOp) continue;
      std::pair<int, int> p (itd->second, ito->second);
      tmp.insert(p);
      currOp += itd->first;
      deficit.erase(itd);                                                       //TODO can I delete while iterating?
      if(deficit.size() == 0) return tmp; //or continue with random times?
    }
  }

  return tmp;
}

}}}
