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
  //TODO hier weiter
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

}}} /* End of namespaces */
