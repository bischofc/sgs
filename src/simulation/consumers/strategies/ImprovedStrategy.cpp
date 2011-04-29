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

#include "ImprovedStrategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

std::multimap<int, int> ImprovedStrategy::getMoves(const std::vector<int> &adjustment,
    std::vector< boost::shared_ptr<Consumer> > devices) {
  std::multimap<int, int> tmp;
  if(devices.empty()) return tmp;

  std::multimap<int, int, helper::Utils::largeToSmallComperator> overplus;
  std::multimap<int, int, helper::Utils::largeToSmallComperator>::iterator ito;
  std::multimap<int, int> deficit;
  std::multimap<int, int>::iterator itd;
  std::vector<int>::iterator ita;
  std::vector< boost::shared_ptr<Consumer> >::iterator itcc, itce;

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

  // for all overplus times do
  for(ito = overplus.begin(); ito != overplus.end(); ito++) {
    itcc = devices.begin();
    itce = devices.end();
    // iterate over all devices
    while(itcc != itce) {
      // and check if they already run at these times
      if((*itcc)->activeInHourOnCurrentDay(ito->second)) {
        // if so, remove those devices and reset the iterators
        itcc = devices.erase(itcc);
        // if the devices list is empty, there is nothing else to do -> return
        if(devices.empty()) return tmp;
        itce = devices.end();
      } else itcc++;
    }
  }

  // for all deficit times do
  for(itd = deficit.begin(); itd != deficit.end(); itd++) {
    itcc = devices.begin();
    itce = devices.end();
    // iterate over all devices
    while(itcc != itce) {
      // and check if they run at these times
      if(!((*itcc)->activeInHourOnCurrentDay(itd->second))) {
        // if not, remove those devices and reset the iterators
        itcc = devices.erase(itcc);
        // if the devices list is empty, there is nothing else to do -> return
        if(devices.empty()) return tmp;
        itce = devices.end();
      } else itcc++;
    }
  }

  // now only those devices are left that are running in the deficit hours and are not running in the overplus hours

  // move the remaining devices from the deficit to the overplus time
  // this does not regard
  //   if the overplus is exceeded
  //   if the deficit is already vanished
  //   devices' runtimes
  //   if the device is moved to a time where it again runs into a deficit

  // welchen energieplan muss ich betrachten (welcher ist movable)?
  // soll ich direkt schieben oder moves zurück geben
  // moveCondition beachten
  // gibt momentan nichts sinnvolles zurück -> gerät entweder gleich verschieben (geräteid/energieplanid zurückliefern) oder
  //   zeiten angeben, aber welche?
//  for(ito = overplus.begin(); ito != overplus.end(); ito++) {
//    int currOp = ito->first;
//    for(itd = deficit.begin(); itd != deficit.end(); itd++) {
//      if(itd->first > currOp) continue;
//      std::pair<int, int> p (itd->second, ito->second);
//      tmp.insert(p);
//      currOp += itd->first;
//      deficit.erase(itd);
//      if(deficit.size() == 0) return tmp; //or continue with random times?
//    }
//  }

  return tmp;
}

}}}
