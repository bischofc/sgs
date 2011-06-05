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
#include "Simulation.h"
#include "exceptions/IOException.h"

namespace simulation {
namespace endpoint {
namespace producer {

Solar::Solar(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("solarPlan.log", Logger::CUSTOM);
  if(!logger2) logger2 = Logger::getInstance("solarIs.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
  std::ifstream solarFactorFile;
  int maxLineSize = 168;
  char line[maxLineSize];

  // fill the solar power curves (plan and is data)
  // (from http://www.transparency.eex.com)
  solarFactorFile.open("./etc/summerSolarPlanFactor.txt");
  if(solarFactorFile.fail()) throw exception::IOException("file not found");
  while(solarFactorFile.getline(line, maxLineSize)) {
    double* tmp = new double[24];
    std::stringstream ss;
    ss << line;
    for(int i = 0; i < 24; i++) ss >> tmp[i];
    solarFactorPlan.push_back(tmp);
  }
  solarFactorFile.close();

  solarFactorFile.open("./etc/summerSolarIsFactor.txt");
  if(solarFactorFile.fail()) throw exception::IOException("file not found");
  while(solarFactorFile.getline(line, maxLineSize)) {
    double* tmp = new double[24];
    std::stringstream ss;
    ss << line;
    for(int i = 0; i < 24; i++) ss >> tmp[i];
    solarFactorIs.push_back(tmp);
  }
  solarFactorFile.close();
}

std::vector<int> Solar::getForecastCurve(int households, int day) {
  if(expdLoad.size() == 0) throw exception::EnergyException("Expected load is not set. Please make sure you called setBaseLoad() before.");
  std::vector<int> tmp (24, 0);
  std::vector<int> tmp2 (24, 0);

  for(int i = 0; i < 24; i++) {
    tmp.at(i) = solarFactorPlan.at(day)[i] * expdLoad.at(i);
    tmp2.at(i) = solarFactorIs.at(day)[i] * expdLoad.at(i);
  }

  int h = Simulation::getTime() / Simulation::getResolution();
  for (unsigned i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(h + i) + "\t" + Logger::toString(tmp.at(i)*households));
    logger2->custom(Logger::toString(h + i) + "\t" + Logger::toString(tmp2.at(i)*households));
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
  for(it = solarFactorPlan.begin(); it != solarFactorPlan.end(); it++) {
    delete [](*it);
  }
  for(it = solarFactorIs.begin(); it != solarFactorIs.end(); it++) {
    delete [](*it);
  }
}

}}} /* end of namespaces */
