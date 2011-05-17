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

#include "ThresholdAccepting.h"
#include "Utils.h" //TODO

namespace simulation {
namespace endpoint {
namespace consumer {

ThresholdAccepting::ThresholdAccepting(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers) : Strategy(adjustment, consumers) {
  threshold = 100;

  BackpackStrategy bs (adjustment, consumers);
  knapsackCosts = getCosts(bs.getMoves());
//  helper::Utils::println(knapsackCosts);
}

int ThresholdAccepting::getCosts(const std::multimap<int, int> &) {
  return 1; //TODO
}

std::multimap<int, int> ThresholdAccepting::getNeighbour(const std::multimap<int, int> &tmp) {
//  std::multimap<int, int> tmp;
  return tmp; //TODO
}

std::multimap<int, int> ThresholdAccepting::getInitialState() {
  BasicStrategy bs (adjustment, consumers);
  return bs.getMoves();
}

std::multimap<int, int> ThresholdAccepting::getMoves() {
  std::multimap<int, int> stateCurr = getInitialState();
  int costsCurr = getCosts(stateCurr);
  std::multimap<int, int> stateBest = stateCurr;
  int costsBest = costsCurr;

  for(int j = 0; j < outerSteps; j++) {
    for(int i = 0; i < innerSteps; i++) {
      std::multimap<int, int> stateNew = getNeighbour(stateCurr);
      int costsNew = getCosts(stateNew);
      if(costsNew - costsCurr < threshold) {
        stateCurr = stateNew;
        costsCurr = costsNew;
      }
      if(costsNew < costsBest) {
        stateBest = stateNew;
        costsBest = costsNew;
      }
    }
    if(costsBest < knapsackCosts) break;//TODO testen
    threshold *= thresholdFactor;
  }

  return stateBest;
}

}}}
