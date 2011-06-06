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
#include "exceptions/EnergyException.h"
#include "exceptions/IOException.h"
#include "LeastSquareFit.h"
#include "Utils.h"

namespace simulation {
namespace endpoint {
namespace producer {

Conventional::Conventional(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("convLoadPlan.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
  int maxLineSize = 168;
  char line[maxLineSize];

  // fill the wind power curves
  // (from http://www.transparency.eex.com)
  std::ifstream windFactorFile;
  windFactorFile.open("./etc/data/summerWindPlanFactor.txt");
  if(windFactorFile.fail()) throw exception::IOException("file not found");
  while(windFactorFile.getline(line, maxLineSize)) {
    double* tmp = new double[24];
    std::stringstream ss;
    ss << line;
    for(int i = 0; i < 24; i++) ss >> tmp[i];
    windFactor.push_back(tmp);
  }
  windFactorFile.close();

  // fill the wind power curves
  // (from http://www.transparency.eex.com)
  std::ifstream solarFactorFile;
  solarFactorFile.open("./etc/data/summerSolarPlanFactor.txt");
  if(solarFactorFile.fail()) throw exception::IOException("file not found");
  while(solarFactorFile.getline(line, maxLineSize)) {
    double* tmp = new double[24];
    std::stringstream ss;
    ss << line;
    for(int i = 0; i < 24; i++) ss >> tmp[i];
    solarFactor.push_back(tmp);
  }
  solarFactorFile.close();
}

std::vector<int> Conventional::getForecastCurve(int households, int day) {
  setEcoLoad(day);
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

std::vector<int> Conventional::getWindLoad(int day) {
  std::vector<int> tmp (24, 0);

  for(int i = 0; i < 24; i++) {
    tmp.at(i) = windFactor.at(day)[i] * expdLoad.at(i);
  }

  // adapt values used for planning on basis of plan values (fitting or other)
  helper::LeastSquareFit lsf (tmp, 4);
  for(int i = 0; i < 24; i++) tmp[i] = 0.85 * lsf[i];//TODO set factor

  return tmp;
}

std::vector<int> Conventional::getSolarLoad(int day) {
  std::vector<int> tmp (24, 0);

  for(int i = 0; i < 24; i++) {
    tmp.at(i) = solarFactor.at(day)[i] * expdLoad.at(i);
  }

  // adapt values used for planning on basis of plan values (fitting or other)
  helper::LeastSquareFit lsf (tmp, 4);
  for(int i = 0; i < 24; i++) tmp[i] = 0.7 * lsf[i];//TODO set factor

  return tmp;
}

void Conventional::setEcoLoad(int day) {
  this->ecoLoad = helper::Utils::addIntVectors(getWindLoad(day), getSolarLoad(day));
}

void Conventional::setExpectedLoad(std::vector<int> expdLoad) {
  if(expdLoad.size() != 24) throw exception::EnergyException("Input has wrong length.");
  BOOST_FOREACH(int i, expdLoad) {
    if(i < 0) throw exception::EnergyException("Negative wattage within load curve is not possible.");
  }
  this->expdLoad = expdLoad;
}

Conventional::~Conventional() {
  std::vector<double*>::iterator it;
  for(it = windFactor.begin(); it != windFactor.end(); it++) {
    delete [](*it);
  }
  for(it = solarFactor.begin(); it != solarFactor.end(); it++) {
    delete [](*it);
  }
}

}}} /* end of namespaces */
