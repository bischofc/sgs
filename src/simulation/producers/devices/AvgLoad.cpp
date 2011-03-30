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

#include "AvgLoad.h"
#include "../../exceptions/EnergyException.h"

namespace simulation {
namespace endpoint {
namespace producer {

AvgLoad::AvgLoad(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("avgload.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
}

std::vector<int> AvgLoad::getForecastCurve(int households) {
  if(baseAndEcoLoad.size() == 0) throw new exception::EnergyException("Base load is not set. Please make sure you called setBaseAndEcoLoad() before.");
  if(refLoad.size() == 0) throw new exception::EnergyException("Expected load is not set. Please make sure you called setExpectedLoad() before.");
  std::vector<int> tmp (24, 0);
  for(int i = 0; i < 24; i++) {
    tmp.at(i) = (baseAndEcoLoad.at(i) >= refLoad.at(i)) ? 0 : refLoad.at(i) - baseAndEcoLoad.at(i);
  }

  for (int i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(i) + "\t" + Logger::toString(tmp.at(i)*households));
  }
  return tmp;
}

void AvgLoad::setBaseAndEcoLoad(std::vector<int> beLoad) {
  if(beLoad.size() != 24) throw new exception::EnergyException("Input has wrong length.");
  for(std::vector<int>::iterator it = beLoad.begin(); it != beLoad.end(); it++) {
    if(*it < 0) throw new exception::EnergyException("Negative wattage within load curve is not possible.");
  }
  baseAndEcoLoad = beLoad;
}

void AvgLoad::setExpectedLoad(std::vector<int> eLoad) {
  if(eLoad.size() != 24) throw new exception::EnergyException("Input has wrong length.");
  for(std::vector<int>::iterator it = eLoad.begin(); it != eLoad.end(); it++) {
    if(*it < 0) throw new exception::EnergyException("Negative wattage within load curve is not possible.");
  }
  refLoad = eLoad;
}

}}} /* end of namespaces */
