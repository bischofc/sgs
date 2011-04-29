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

#include "BaseLoad.h"
#include "Simulation.h"
#include "../../exceptions/EnergyException.h"

namespace simulation {
namespace endpoint {
namespace producer {

BaseLoad::BaseLoad(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("baseload.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
  wattage = -1;
}

void BaseLoad::setWattage(int wattage) {
  if(wattage < 0) throw exception::EnergyException("Negative wattage is not possible.");
  this->wattage = wattage;
}

std::vector<int> BaseLoad::getForecastCurve(int households) {
  if(wattage < 0) throw exception::EnergyException("Wattage is not set. Please make sure you called setWattage() before.");
  std::vector<int> tmp (24, wattage);

  int hour = Simulation::getTime() / Simulation::getResolution();
  for (unsigned i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(hour + i) + "\t" + Logger::toString(tmp.at(i)*households));
  }
  return tmp;
}

}}} /* end of namespaces */
