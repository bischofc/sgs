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
#include "BasicStrategy.h"
#include "ImprovedStrategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

boost::shared_ptr<Logger> ThresholdAccepting::logger;

ThresholdAccepting::ThresholdAccepting(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers) : Strategy(adjustment, consumers) {
  if(!logger) logger = Logger::getInstance("simulation.log");
  threshold = 10000;

  ImprovedStrategy bs (adjustment, consumers);
  referenceCosts = getCosts(bs.getMoves()) * 0.7;
}

int ThresholdAccepting::getCosts(const std::vector<Move> &moves) {
  int costs = 0;
  std::vector<int> adjustment = this->adjustment;
  BOOST_FOREACH(Move m, moves) {
    costs -= getEnergyBalance(adjustment, m.starttime, m.to, m.runtime, m.device->getConnectedLoad());
    updateAdjustment(adjustment, m.starttime, m.to, m.runtime, m.device->getConnectedLoad());
  }
  return costs;
}

// either removes, adds or replaces a move
std::vector<Move> ThresholdAccepting::getNeighbour(const std::vector<Move> &moves) {

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
  if(neighbor.size() == 0) {
    // if(newMoves.size() == 0) there is nothing to do
    // else add random newMove
    if(newMoves.size() > 0) neighbor.push_back(newMoves[helper::RandomNumbers::getRandom(0, newMoves.size()-1)]);
  } else {
    // remove random move
    if(newMoves.size() == 0) neighbor.erase(neighbor.begin() + helper::RandomNumbers::getRandom(0, neighbor.size()-1));
    // more actions are possible here
    else {
      // 3 possible choices: delete, add and replace each with a probability of 0.33
      // action: delete
      if(helper::RandomNumbers::getRandom() < 0.33) {
        neighbor.erase(neighbor.begin() + helper::RandomNumbers::getRandom(0, neighbor.size()-1));
      } else {
        // pick element from newMoves and check if already in neigbour
        Move tm = newMoves[helper::RandomNumbers::getRandom(0, newMoves.size()-1)];
        std::vector<Move>::const_iterator it = findDeviceOfMoveInMoveList(neighbor, tm);
        // action: add
        if(it == neighbor.end() && helper::RandomNumbers::getRandom() < 0.5) {
          neighbor.push_back(tm);
        //action: replace
        } else if(it != neighbor.end() && helper::RandomNumbers::getRandom() < 0.5) {
          helper::Utils::deleteFromVector(neighbor, it);
          neighbor.push_back(tm);
        } else {
          // if nothing can be done do another iteration (eventually it picks delete and thereby ends recursion)
          logger->debug("Choice of action failed: do another recursion");
          neighbor = getNeighbour(neighbor);
        }
      }
    }
  }
  return neighbor;
}

std::vector<Move>::const_iterator ThresholdAccepting::findDeviceOfMoveInMoveList(const std::vector<Move> &vec, const Move &m) {
  boost::shared_ptr<Consumer> device = m.device;
  for(std::vector<Move>::const_iterator it = vec.begin(); it != vec.end(); it++) {
    if((*it).device == device) return it;
  }
  return vec.end();
}

std::vector<Move> ThresholdAccepting::getInitialState() {
  ImprovedStrategy rs (adjustment, consumers);
  std::vector<Move> moves = rs.getMoves();
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
    if(costsBest < referenceCosts) break;
    threshold *= thresholdFactor;
  }

  return stateBest;
}

}}}
