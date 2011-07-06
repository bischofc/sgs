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

#include "BackpackStrategy.h"
#include <algorithm>
#include <boost/foreach.hpp>
#include <exception>
#include "Utils.h"

namespace simulation {
namespace endpoint {
namespace consumer {

BackpackStrategy::BackpackStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers
    ) : Strategy(adjustment, consumers) {
//  costs = -1;
//  profit = -1;
}

std::vector<Move> BackpackStrategy::getMoves() {
  std::vector< Move > moves;

  // check for overplusses and deficits
  // calculate total overplus
  std::vector<int> overplus;
  std::vector<int> deficit;
  int boundary = 0;
  for(unsigned i=0; i < adjustment.size(); i++) {
    int v = adjustment.at(i);
    if(v > 0) {
      overplus.push_back(i);
      boundary += adjustment.at(i);
    }
    else if(v < 0) deficit.push_back(i);
  }

  // check which devices are regarded
  // add profit and cost info
  // count elements
  std::vector<BackpackElement> regardedElements;
  int numberOfElements;
  BOOST_FOREACH(boost::shared_ptr<Consumer> tcIt, consumers) {
    BOOST_FOREACH(int o, overplus) {
      BOOST_FOREACH(int d, deficit) {
        int a, b;
        if(tcIt->isMovable(d, o, a, b)) {
          BackpackElement be (tcIt, tcIt->getConnectedLoad(), getEnergyBalance(adjustment, a, o, b, tcIt->getConnectedLoad()), d, o, a, b);
          std::vector<BackpackElement>::const_iterator it = helper::Utils::searchInVector(regardedElements, be);
          if(it != regardedElements.end()) helper::Utils::deleteFromVector(regardedElements, it);
          regardedElements.push_back(be);
        }
  } } }
  numberOfElements = regardedElements.size();

  // create and initialize matrices
  int dynamicProfitTable[numberOfElements + 2][boundary + 1];
  int dynamicElementTable[numberOfElements + 2][boundary + 1];
  for(int i = 0; i < numberOfElements+2; i++) for(int j = 0; j <= boundary; j++) {
      dynamicProfitTable[i][j] = 0;
      dynamicElementTable[i][j] = 0;
  }

  // pack the bag
  for(int i = numberOfElements; i >= 1; i--) {
    int currEltId = i-1;
    BackpackElement currElt = regardedElements.at(currEltId);
    for(int j = 1; j <= boundary; j++) {
      // update matrix values
      if(currElt.weight <= j) {
        if(currElt.profit + dynamicProfitTable[i+1][j-currElt.weight] > dynamicProfitTable[i+1][j]) {
          dynamicProfitTable[i][j] = currElt.profit + dynamicProfitTable[i+1][j-currElt.weight];
          dynamicElementTable[i][j] = currEltId;
        } else {
          dynamicProfitTable[i][j] = dynamicProfitTable[i+1][j];
          dynamicElementTable[i][j] = dynamicElementTable[i+1][j];
        }
      } else {
        dynamicProfitTable[i][j] = dynamicProfitTable[i+1][j];
        dynamicElementTable[i][j] = dynamicElementTable[i+1][j];
      }
    }
  }
//  profit = dynamicProfitTable[1][boundary];

  // initialize element matrix for traversal to identify packed items
  std::vector<BackpackElement> elementsInBackpack;
  int sumWeight = 0;
  int sumProfit = 0;
  int i = 1;
  int j = boundary;
  while(sumProfit != dynamicProfitTable[1][boundary]) {
    int currentEltId = dynamicElementTable[i][j];
    BackpackElement item = regardedElements.at(currentEltId);
    elementsInBackpack.push_back(item);
    sumWeight += item.weight;
    sumProfit += item.profit;
    j -= item.weight;
    i++;
    while(dynamicElementTable[i][j] == currentEltId) i++;
  }

  // extract moves from elements in backpack
//  costs = 0;
  BOOST_FOREACH(BackpackElement elt, elementsInBackpack) {
    Move m (elt.consumer, elt.from, elt.to, elt.starttime, elt.runtime);
    moves.push_back(m);
//    costs += elt.weight;
  }

  return moves;
}

//int BackpackStrategy::getCosts() {
//  if(costs == -1) getMoves();
//  return costs;
//}
//
//int BackpackStrategy::getProfit() {
//  if(profit == -1) getMoves();
//  return profit;
//}

}}}
