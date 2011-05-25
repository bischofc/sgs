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

#include "Solar.h"
#include "RandomNumbers.h"
#include "Simulation.h"
#include "exceptions/IOException.h"

namespace simulation {
namespace endpoint {
namespace producer {

Solar::Solar(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("solar.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
  days = 0;

  // fill the solar power curves
  // (from http://www.transparency.eex.com)
  std::ifstream solarFactorFile;
  int maxLineSize = 168;
  char line[maxLineSize];

  solarFactorFile.open("./etc/springSolarIsFactor.txt");
  if(solarFactorFile.fail()) throw exception::IOException("file not found");
  while(solarFactorFile.getline(line, maxLineSize)) {
    double* tmp = new double[24];
    std::stringstream ss;
    ss << line;
    for(int i = 0; i < 24; i++) ss >> tmp[i];
    solarFactor.push_back(tmp);
    days++;
  }
  solarFactorFile.close();
}

std::vector<int> Solar::getForecastCurve(int households) {
  if(expdLoad.size() == 0) throw exception::EnergyException("Expected load is not set. Please make sure you called setBaseLoad() before.");
  std::vector<int> tmp (24, 0);
  int day = helper::RandomNumbers::getRandom(0, days-1);

  for(int i = 0; i < 24; i++) {
    tmp.at(i) = solarFactor.at(day)[i] * expdLoad.at(i);
  }
  //TODO sanity check

  int h = Simulation::getTime() / Simulation::getResolution();
  for (unsigned i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(h + i) + "\t" + Logger::toString(tmp.at(i)*households));
  }
  return tmp;
}

void Solar::setExpectedLoad(std::vector<int> expdLoad) {
  if(expdLoad.size() != 24) throw exception::EnergyException("Input has wrong length.");
  for(std::vector<int>::iterator it = expdLoad.begin(); it != expdLoad.end(); it++) {
    if(*it < 0) throw exception::EnergyException("Negative wattage within load curve is not possible.");
  }
  this->expdLoad = expdLoad;
}

Solar::~Solar() {
  std::vector<double*>::iterator it;
  for(it = solarFactor.begin(); it != solarFactor.end(); it++) {
    delete [](*it);
  }
}

}}} /* end of namespaces */
