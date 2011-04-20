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

#include "ConsumerOwner.h"
#include "RandomNumbers.h"
#include "strategies/BasicStrategy.h"
#include "strategies/BackpackStrategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

ConsumerOwner::ConsumerOwner(std::string ownerId) {
  this->id = ownerId;
}

std::string ConsumerOwner::getId() {
  return 0;
}

int ConsumerOwner::getWattage() throw (exception::EnergyException){
  int wattage = 0;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerList.begin();
                  it != this->consumerList.end(); it++) {
    wattage += (*it)->getCurrentWattage();
  }
  return wattage;
}

void ConsumerOwner::adjustLoad(std::vector<int> adjustment) {
  // check size of adjustment
  if(adjustment.size() != 24) {
    throw exception::EnergyException("Adjustment vector has wrong size. Skipping.");
    return;
  }

  // get move strategy
//  int profit;//TODO
//  vector<int> a (23, 0);//TODO
//  vector<BackpackElement> b;//TODO
//  std::multimap<int, int> moves = BackpackStrategy::getMoves(adjustment, a, profit, b);
  std::multimap<int, int> moves = BasicStrategy::getMoves(adjustment);

  // reset the original runtimes before moving
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = consumerList.begin(); it != consumerList.end(); it++) {
    (*it)->resetEnergyPlans();
    for(std::multimap<int, int>::iterator im = moves.begin(); im != moves.end(); im++) {
      if(moveCondition()) {
        (*it)->move(im->first, im->second);
      }
    }
  }
}

void ConsumerOwner::addConsumer(boost::shared_ptr<Consumer> c) {
  this->consumerList.push_back(c);
}

/*
 * Decides in which case the load adjustment is regarded in each household
 * if fulfilled: true, otherwise: false
 */
bool ConsumerOwner::moveCondition() {
  // for the beginning: move with a probability of 90%
//  return (helper::RandomNumbers::getRandom() < 0.9) ? true : false;
  return true;
}

}}} /* End of namespaces */
