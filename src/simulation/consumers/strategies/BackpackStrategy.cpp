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

namespace simulation {
namespace endpoint {
namespace consumer {

BackpackStrategy::BackpackStrategy(const std::vector<int> &adjustment,
    const std::vector< boost::shared_ptr<Consumer> > &consumers
    ) : Strategy(adjustment, consumers) {}

std::multimap<int, int> BackpackStrategy::getMoves() {
  std::vector<int> profit (24, 0);//TODO profit für gegenstand (zu jeweiligem gewicht) -> vllt kostenfunktion verwenden
  int highestProfit;
  std::vector<BackpackElement> elementsInBackpack;

  std::multimap<int, int> tmp;
  std::vector<BackpackElement> elements;
  int boundary = 0;
  int numberOfElements = 0;

  // prepare and count elements, calculate boundary
  for(unsigned i=0; i < adjustment.size(); i++) {
    int v = adjustment.at(i);
    if(v > 0) {
      boundary += v;
    } else if(v < 0){
      BackpackElement e (i, -v, profit.at(i));
      elements.push_back(e);
      numberOfElements++;
    }
  }

  // create and initialize matrices
  int dynamicProfitTable[numberOfElements + 2][boundary + 1];
  for(int i = 0; i < numberOfElements+2; i++) for(int j = 0; j <= boundary; j++) dynamicProfitTable[i][j] = 0;
  int dynamicElementTable[numberOfElements + 2][boundary + 1];
  for(int i = 0; i < numberOfElements+2; i++) for(int j = 0; j <= boundary; j++) dynamicElementTable[i][j] = 0;

  // do the backpacking
  std::multimap<int, int> elementsToBeMoved;
  for(int i = numberOfElements; i >= 1; i--) {
    int currEltId = i-1;
    BackpackElement currElt = elements.at(currEltId);
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
  highestProfit = dynamicProfitTable[1][boundary];

  // initialize element matrix for traversal to identify packed items
  int sumWeight = 0;
  int sumProfit = 0;
  int i = 1;
  int j = boundary;
  while(sumProfit != dynamicProfitTable[1][boundary]) {
    int currentEltId = dynamicElementTable[i][j];
    BackpackElement item = elements.at(currentEltId);
    elementsInBackpack.push_back(item);
    sumWeight += item.weight;
    sumProfit += item.profit;
    j -= item.weight;
    i++;
    while(dynamicElementTable[i][j] == currentEltId) i++;
  }

  return tmp;
}

}}}
