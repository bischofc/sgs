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

#include "Medium.h"
#include "producers/ProducerOwner.h"
#include "consumers/ConsumerOwner.h"
#include "Simulation.h"

namespace simulation {
namespace medium {

Medium::Medium(std::string name) {
  wattage = 0;
  producerOwnerSet = false;
  this->name = name;
}

void Medium::registerConsumerOwner(boost::shared_ptr<endpoint::consumer::ConsumerOwner> co) {
  this->consumerOwnerList.push_back(co);
}

void Medium::registerProducerOwner(boost::shared_ptr<endpoint::producer::ProducerOwner> po) {
  if(producerOwnerSet) {
    throw exception::ParserException("Producer cannot be registered, one already exists. Check config file.");
  } else {
    producerOwner = po;
    producerOwnerSet = true;
  }
}

void Medium::oneStep() throw (exception::EnergyException) {
  // check if producer exists
  if(!producerOwnerSet) {
    throw exception::NoSuchDeviceException("No producer owner found. Check config file");   //TODO exit!
  }

  // initialize step
  wattage = 0;

  // get load adjustment from producer owner
  loadAdjustment = producerOwner->getLoadAdjustment(getNumberOfConsumers());

  // send load adjustment if available and check energy consumption
  for(std::vector< boost::shared_ptr<endpoint::consumer::ConsumerOwner> >::iterator it = this->consumerOwnerList.begin();
                  it < this->consumerOwnerList.end(); it++) {
    boost::shared_ptr<endpoint::consumer::ConsumerOwner> co = *it;
    if(!loadAdjustment.empty()) co->adjustLoad(loadAdjustment);
    double tmp = co->getWattage();
    wattage += tmp;
  }
}

int Medium::getCurrentWattage() {
  return wattage;
}

int Medium::getNumberOfConsumers() {
  return consumerOwnerList.size();
}


} /* End of namespace simulation::medium */
} /* End of namespace simulation */
