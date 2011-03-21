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

//TODO
#include <stdio.h>

namespace simulation {
namespace endpoint {
namespace consumer {

ConsumerOwner::ConsumerOwner(std::string ownerId) {
  this->id = ownerId;
}

std::string ConsumerOwner::getId() {
  return 0;
}

double ConsumerOwner::getEnergy() throw (exception::EnergyException){
  double energy = 0.0;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerList.begin();
                  it != this->consumerList.end(); it++) {
    energy += (*it)->getCurrentEnergy();
  }
  return energy;
}

void ConsumerOwner::adjustLoad(std::vector<double> adjustment) {
  // check size of adjustment
  if(adjustment.size() != 24) {
    throw exception::EnergyException("Adjustment vector has wrong size. Skipping.");
    return;
  }

  // get strategy and apply moves
  std::multimap<int, int> moves = moveStrategy(adjustment);
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = consumerList.begin(); it != consumerList.end(); it++) {
    for(std::multimap<int, int>::iterator im = moves.begin(); im != moves.end(); im++) {
      if(moveCondition()) {
        (*it)->move(im->first, im->second);
      }
    }
  }
}

void ConsumerOwner::dump(std::ostringstream &out) {
  out << "    ConsumerOwner-Id: " << this->id << std::endl;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerList.begin();
      it != this->consumerList.end(); it++) {
    (*it)->dump(out);
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

/*
 * Implements strategy of how to transform the adjustment to specific times
 * Result is a map with one or more (start time, end time) pair(s)
 */
std::multimap<int, int> ConsumerOwner::moveStrategy(std::vector<double> adjustment) {
  std::multimap<int, int> tmp;
  std::multimap<double, int> overplus, deficit;
  std::multimap<double, int>::iterator ito, itd;
//  std::vector< std::pair<double, int> > toDel;
//  std::vector< std::pair<double, int> >::iterator delit;

  for(unsigned i=0; i < adjustment.size(); i++) {
    double v = adjustment.at(i);
    if(v > 0) {
      std::pair<double, int> p (v, i);
      overplus.insert(p);
    } else if(v < 0){
      std::pair<double, int> p (v, i);
      deficit.insert(p);
    }
  }

  // TODO improve algorithm (very basic, does not regard many things including already moved energy plans)
  for(ito = overplus.begin(); ito != overplus.end(); ito++) {
    double currOp = ito->first;
    for(itd = deficit.begin(); itd != deficit.end(); itd++) {
      if(currOp + itd->first > 0) {
        std::pair<int, int> p (itd->second, ito->second);
        tmp.insert(p);
        currOp += itd->first;
        deficit.erase(itd);                                                     //TODO can I delete while iterating?
        if(deficit.size() == 0) return tmp; //or continue with random times?
      }
    }
  }

  return tmp;
}

}}} /* End of namespaces */
