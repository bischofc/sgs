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
#include "Utils.h"

namespace simulation {
namespace endpoint {
namespace consumer {

BackpackStrategy::BackpackStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers
    ) : Strategy(adjustment, consumers) {}

std::vector<Move> BackpackStrategy::getMoves() {
  std::vector< Move > moves;
//  std::vector<int> profit (24, 0);//TODO profit für gegenstand (zu jeweiligem gewicht) -> vllt kostenfunktion verwenden
//  int highestProfit;
//  std::vector<BackpackElement> elementsInBackpack;
//
//  std::multimap<int, int> tmp;


  // check for overplusses and deficits
  std::vector<int> overplus;
  std::vector<int> deficit;
  for(unsigned i=0; i < adjustment.size(); i++) {
    int v = adjustment.at(i);
    if(v > 0) overplus.push_back(i);
    else if(v < 0) deficit.push_back(i);
  }

  // check which devices are regarded
  // add profit and cost info
  // count elements
  std::vector<BackpackElement> regardedElements;
  int numberOfElements;
  BOOST_FOREACH(boost::shared_ptr<Consumer> tcIt, consumers) {
    helper::Utils::println("new consumer");
    for(unsigned i = 0; i < overplus.size(); i++) {
      for(unsigned j; j < deficit.size(); j++) {
        int a, b;
        helper::Utils::print("check to move");//TODO hier weiter: wird nicht ausgegeben overplus und deficit checken
        if(tcIt->isMovable(j, i, a, b)) {
          BackpackElement be (tcIt, tcIt->getConnectedLoad(), getEnergyBalance(a, i, b, tcIt->getConnectedLoad()));
          std::vector<BackpackElement>::iterator it = helper::Utils::searchInVector(regardedElements, be);
          if(it != regardedElements.end()) { regardedElements.erase(it); helper::Utils::print("d"); }
          regardedElements.push_back(be);
          helper::Utils::print("a");
        }
      }
    }
  }
  numberOfElements = regardedElements.size();

  // prepare and count elements, calculate boundary
  int boundary = 0;
  for(unsigned i=0; i < adjustment.size(); i++) {
    if(adjustment.at(i) > 0) boundary += adjustment.at(i);
  }

  // create and initialize matrices
  int dynamicProfitTable[numberOfElements + 2][boundary + 1];
  for(int i = 0; i < numberOfElements+2; i++) for(int j = 0; j <= boundary; j++) dynamicProfitTable[i][j] = 0;
  int dynamicElementTable[numberOfElements + 2][boundary + 1];
  for(int i = 0; i < numberOfElements+2; i++) for(int j = 0; j <= boundary; j++) dynamicElementTable[i][j] = 0;

//  // do the backpacking
//  std::multimap<int, int> elementsToBeMoved;
//  for(int i = numberOfElements; i >= 1; i--) {
//    int currEltId = i-1;
//    BackpackElement currElt = elements.at(currEltId);
//    for(int j = 1; j <= boundary; j++) {
//      // update matrix values
//      if(currElt.weight <= j) {
//        if(currElt.profit + dynamicProfitTable[i+1][j-currElt.weight] > dynamicProfitTable[i+1][j]) {
//          dynamicProfitTable[i][j] = currElt.profit + dynamicProfitTable[i+1][j-currElt.weight];
//          dynamicElementTable[i][j] = currEltId;
//        } else {
//          dynamicProfitTable[i][j] = dynamicProfitTable[i+1][j];
//          dynamicElementTable[i][j] = dynamicElementTable[i+1][j];
//        }
//      } else {
//        dynamicProfitTable[i][j] = dynamicProfitTable[i+1][j];
//        dynamicElementTable[i][j] = dynamicElementTable[i+1][j];
//      }
//    }
//  }
//  highestProfit = dynamicProfitTable[1][boundary];
//
//  // initialize element matrix for traversal to identify packed items
//  int sumWeight = 0;
//  int sumProfit = 0;
//  int i = 1;
//  int j = boundary;
//  while(sumProfit != dynamicProfitTable[1][boundary]) {
//    int currentEltId = dynamicElementTable[i][j];
//    BackpackElement item = elements.at(currentEltId);
//    elementsInBackpack.push_back(item);
//    sumWeight += item.weight;
//    sumProfit += item.profit;
//    j -= item.weight;
//    i++;
//    while(dynamicElementTable[i][j] == currentEltId) i++;
//  }

  return moves;
}

}}}
