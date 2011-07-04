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

#include <boost/foreach.hpp>
#include "BasicStrategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

BasicStrategy::BasicStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers
    ) : Strategy(adjustment, consumers) {}

/*  Move all devices that run in deficit time slots AND not in overplus time slots.
 *  This does especially not regard
 *    if the overplus is exceeded
 *    if the device is moved to a time where it again runs into a deficit
 */
std::vector<Move> BasicStrategy::getMoves() {
  std::vector< Move > moves;
  if(consumers.empty()) return moves;
  std::vector< boost::shared_ptr<Consumer> > tmpConsumers = consumers;
  boost::shared_ptr<Consumer> tcIt;
  std::vector<int> overplus;
  std::vector<int> deficit;
  std::vector<int> tmpAdjustment = adjustment;

  // check for overplusses and deficits
  for(unsigned i=0; i < tmpAdjustment.size(); i++) {
    int v = tmpAdjustment.at(i);
    if(v > 0) overplus.push_back(i);
    else if(v < 0) deficit.push_back(i);
  }

  bool moved;
  BOOST_FOREACH(tcIt, tmpConsumers) {
    moved = false;
    BOOST_FOREACH(int ito, overplus) {
      int tmpOpls = tmpAdjustment.at(ito);
      BOOST_FOREACH(int itd, deficit) {
        int a, b;
        int consumerLoad = tcIt->getConnectedLoad();
        if(!moved && tmpOpls > 0 && -tmpAdjustment.at(itd) > 0 && tcIt->isMovable(itd, ito, a, b)) {
          Move m (tcIt, itd, ito, a, b);
          moves.push_back(m);
          moved = true;
          tmpOpls -= consumerLoad;
          updateAdjustment(tmpAdjustment, a, ito, b, consumerLoad);
        }
      }
    }
  }

  return moves;
}

}}}
