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

#include <boost/foreach.hpp>
#include "Conventional.h"
#include "Simulation.h"
#include "../../exceptions/EnergyException.h"
#include "Utils.h"
#include "LeastSquareFit.h"

namespace simulation {
namespace endpoint {
namespace producer {

Conventional::Conventional(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("convload.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
}

std::vector<int> Conventional::getForecastCurve(int households) {
  if(ecoLoad.size() == 0) throw exception::EnergyException("Eco load is not set. Please make sure you called setEcoLoad() before.");
  if(expdLoad.size() == 0) throw exception::EnergyException("Expected load is not set. Please make sure you called setExpectedLoad() before.");
  std::vector<int> tmp (24, 0);
  for(int i = 0; i < 24; i++) {
    tmp.at(i) = (ecoLoad.at(i) >= expdLoad.at(i)) ? 0 : expdLoad.at(i) - ecoLoad.at(i);
  }

  int hour = Simulation::getTime() / Simulation::getResolution();
  for (unsigned i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(hour + i) + "\t" + Logger::toString(tmp.at(i)*households));
  }
  return tmp;
}

void Conventional::setEcoLoad(std::vector<int> ecoLoad) {
  if(ecoLoad.size() != 24) throw exception::EnergyException("Input has wrong length.");
  BOOST_FOREACH(int i, ecoLoad) {
    if(i < 0) throw exception::EnergyException("Negative wattage within load curve is not possible.");
  }

  helper::LeastSquareFit lsf (ecoLoad, 4);
  std::vector<int> tmp;
  for(int i = 0; i < 24; i++) tmp.push_back(lsf[i]);
//  this->ecoLoad = helper::Utils::linearRegression(ecoLoad);
  this->ecoLoad = tmp;
}

void Conventional::setExpectedLoad(std::vector<int> expdLoad) {
  if(expdLoad.size() != 24) throw exception::EnergyException("Input has wrong length.");
  BOOST_FOREACH(int i, expdLoad) {
    if(i < 0) throw exception::EnergyException("Negative wattage within load curve is not possible.");
  }
  this->expdLoad = expdLoad;
}

}}} /* end of namespaces */
