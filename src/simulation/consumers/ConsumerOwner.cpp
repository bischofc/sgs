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

#include "boost/foreach.hpp"
#include "ConsumerOwner.h"
#include "RandomNumbers.h"
#include "Simulation.h"
#include "strategies/BasicStrategy.h"
#include "strategies/BackpackStrategy.h"
#include "strategies/ImprovedStrategy.h"
#include "strategies/ThresholdAccepting.h"
//#include "Utils.h"//TODO

namespace simulation {
namespace endpoint {
namespace consumer {

boost::shared_ptr<Logger> ConsumerOwner::logger;

ConsumerOwner::ConsumerOwner(std::string ownerId) {
  if(!logger) logger = Logger::getInstance("energyMovement.log", Logger::CUSTOM);
  this->id = ownerId;
}

std::string ConsumerOwner::getId() {
  return 0;
}

int ConsumerOwner::getWattage() throw (exception::EnergyException) {
  int wattage = 0;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerListFixed.begin();
                  it != this->consumerListFixed.end(); it++) {
    wattage += (*it)->getCurrentWattage();
  }
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerListMovable.begin();
                  it != this->consumerListMovable.end(); it++) {
    wattage += (*it)->getCurrentWattage();
  }
  return wattage;
}

void ConsumerOwner::reset() {
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerListMovable.begin();
                  it != this->consumerListMovable.end(); it++) {
    (*it)->resetEnergyPlans();
  }
}

void ConsumerOwner::adjustLoad(std::vector<int> adjustment) {
  // check size of adjustment
  if(adjustment.size() != 24) {
    throw exception::EnergyException("Adjustment vector has wrong size. Skipping.");
    return;
  }

  // get move strategy
  ThresholdAccepting strategy (adjustment, consumerListMovable);
  std::vector<Move> moves = strategy.getMoves();

  // move devices
  int energy = 0;
  if(true) {
    BOOST_FOREACH(Move m, moves) {
      energy += m.device->move(m.from, m.to);
//      helper::Utils::print(m.from);//TODO
    }
  }
  logger->custom(Logger::toString(Simulation::getTime()) + "\t" + Logger::toString(energy));
}

void ConsumerOwner::addConsumer(boost::shared_ptr<Consumer> c) {
  if(c->isMovable()) consumerListMovable.push_back(c);
  else consumerListFixed.push_back(c);
}

}}} /* End of namespaces */
