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
#include "ImprovedStrategy.h"
#include "Simulation.h"

namespace simulation {
namespace endpoint {
namespace consumer {

ImprovedStrategy::ImprovedStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers) : Strategy(adjustment, consumers) {}

std::vector<Move> ImprovedStrategy::getMoves() {
  std::vector< Move > moves;
  if(consumers.empty()) return moves;

  int a, b;
  std::vector<int> tmpAdjustment = adjustment;
  bool moved;
  for(std::vector< boost::shared_ptr<Consumer> >::const_iterator it = consumers.begin(); it != consumers.end(); it++) {
    moved = false;
    for(unsigned i = 0; i < 24; i++) {
      if(adjustment[i] < 0) {
        for(unsigned j = 0; j < 24; j++) {
          if(!moved && adjustment[j] > 0 && (*it)->isMovable(i, j, a, b)) {
            a = (a + Simulation::getResolution()/2) / Simulation::getResolution();
            b = (b + Simulation::getResolution()/2) / Simulation::getResolution();
            if(isEnergyBalancePositive(tmpAdjustment, a, j, b, (*it)->getConnectedLoad())) {
              updateAdjustment(tmpAdjustment, a, j, b, (*it)->getConnectedLoad());
              Move m (*it, i, j, a, b);
              moves.push_back(m);
              moved = true;
  }}}}}}

  return moves;
}

}}}
