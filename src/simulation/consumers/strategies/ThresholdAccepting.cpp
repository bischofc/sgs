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
#include "ThresholdAccepting.h"
#include "RandomNumbers.h"
#include "BasicStrategy.h" //TODO initiale Konfiguration
#include "ImprovedStrategy.h" //TODO "beste Strategie"
#include "BackpackStrategy.h" //TODO "beste Strategie"
#include "Utils.h" //TODO

namespace simulation {
namespace endpoint {
namespace consumer {

ThresholdAccepting::ThresholdAccepting(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers) : Strategy(adjustment, consumers) {
  threshold = 100;

  ImprovedStrategy bs (adjustment, consumers);
  referenceCosts = getCosts(bs.getMoves());
}

int ThresholdAccepting::getCosts(const std::vector<Move> &moves) {
  int costs = 0;
  std::vector<int> adjustment = this->adjustment;
  BOOST_FOREACH(Move m, moves) {
    costs -= getEnergyBalance(adjustment, m.starttime, m.to, m.runtime, m.device->getConnectedLoad()); // TODO maybe use different cost function
    updateAdjustment(adjustment, m.starttime, m.to, m.runtime, m.device->getConnectedLoad());
  }
  return costs;
}

// either removes, adds or replaces a move
std::vector<Move> ThresholdAccepting::getNeighbour(const std::vector<Move> &moves) { //TODO

  // get adjustment for current moves
  std::vector<int> tmpAdjustment = adjustment;
  BOOST_FOREACH(Move m, moves) {
    updateAdjustment(tmpAdjustment, m.starttime, m.to, m.runtime, m.device->getConnectedLoad());
  }

  // check for overplusses and deficits
  std::vector<int> overplus;
  std::vector<int> deficit;
  for(unsigned i=0; i < tmpAdjustment.size(); i++) {
    int v = tmpAdjustment.at(i);
    if(v > 0) overplus.push_back(i);
    else if(v < 0) deficit.push_back(i);
  }

  // get all possible moves
  std::vector< boost::shared_ptr<Consumer> > tmpConsumers = consumers;
  boost::shared_ptr<Consumer> tcIt;
  std::vector<Move> newMoves;
  BOOST_FOREACH(tcIt, tmpConsumers) {
    BOOST_FOREACH(int ito, overplus) {
      BOOST_FOREACH(int itd, deficit) {
        int a, b;
        if(tcIt->isMovable(itd, ito, a, b)) {
          Move m (tcIt, itd, ito, a, b);
          newMoves.push_back(m);
  } } } }

  // choose and perform action
  std::vector<Move> neighbor = moves;
  if(moves.size() == 0) {
    // there is nothing to do
    if(newMoves.size() == 0) return neighbor;
    // add random newMove
    else neighbor.push_back(newMoves[helper::RandomNumbers::getRandom(0, newMoves.size()-1)]);
  } else {
    // remove random move
    if(newMoves.size() == 0) neighbor.erase(neighbor.begin() + helper::RandomNumbers::getRandom(0, neighbor.size()-1));
    // more actions are possible here
    else {
      //TODO hier weiter
    }
  }

  return neighbor;
}

std::vector<Move> ThresholdAccepting::getInitialState() {
  BasicStrategy rs (adjustment, consumers);  // TODO Improved Strategy
  std::vector<Move> moves = rs.getMoves();
  helper::Utils::print(moves.size());
  return moves;
}

std::vector<Move> ThresholdAccepting::getMoves() {
  std::vector<Move> stateCurr = getInitialState();
  int costsCurr = getCosts(stateCurr);
  std::vector<Move> stateBest = stateCurr;
  int costsBest = costsCurr;

  for(int j = 0; j < outerSteps; j++) {
    for(int i = 0; i < innerSteps; i++) {
      std::vector<Move> stateNew = getNeighbour(stateCurr);
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
    if(costsBest < referenceCosts) break;//TODO testen
    threshold *= thresholdFactor;
  }

  helper::Utils::print(stateBest.size());
  helper::Utils::println("");

  return stateBest;
}

}}}
