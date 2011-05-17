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

namespace simulation {
namespace endpoint {
namespace consumer {

BasicStrategy::BasicStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers
    ) : Strategy(adjustment, consumers) {}

std::multimap<int, int> BasicStrategy::getMoves() {
  std::multimap<int, int> tmp;
  std::multimap<int, int, helper::Utils::largeToSmallComperator> overplus;
  std::multimap<int, int, helper::Utils::largeToSmallComperator>::iterator ito;
  std::multimap<int, int> deficit;
  std::multimap<int, int>::iterator itd;

  // check for overplusses and deficits
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

  // this does not regard
  //   if the overplus is exceeded
  //   if the deficit is already vanished
  //   devices' runtimes
  //   if the device is moved to a time where it again runs into a deficit
  for(ito = overplus.begin(); ito != overplus.end(); ito++) {
    int currOp = ito->first;
    for(itd = deficit.begin(); itd != deficit.end(); itd++) {
      if(itd->first > currOp) continue;
      std::pair<int, int> p (itd->second, ito->second);
      tmp.insert(p);
      currOp += itd->first;
      deficit.erase(itd);
      if(deficit.size() == 0) return tmp; //or continue with random times?
    }
  }

  return tmp;
}

}}}
