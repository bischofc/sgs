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

#include <boost/pointer_cast.hpp>
#include <limits.h>
#include "ProducerOwner.h"
#include "DeviceFactory.h"
#include "Simulation.h"
#include "Utils.h"
#include "exceptions/IOException.h"

#include "devices/AvgLoad.h"
#include "devices/BaseLoad.h"
#include "devices/Windmill.h"

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  if(!logger) logger = Logger::getInstance("adjustment.log", Logger::CUSTOM);
  if(!logger2) logger2 = Logger::getInstance("expectedLoad.log", Logger::CUSTOM);//TODO schöner machen (umbenennen oder so)
  this->id = ownerId;

  // fill the reference load curves
  // (from a previous experiment: mean per hour per household)
  std::ifstream expectedLoadFile;
  expectedLoadFile.open("./etc/expectedLoad");
  if(expectedLoadFile.fail()) throw new exception::IOException("file not found");
  int i, j;
  i = j = 0;
  while(i != 7) {
    expectedLoadFile >> referenceLoadCurves[i][j++];                            //TODO not secure
    if(j==24) {i++; j=0;}
  }
  expectedLoadFile.close();
}

std::string ProducerOwner::getId() {
  return 0;
}

// returns an empty vector if no adjustment is necessary
// otherwise a vector with 24 elements
std::vector<int> ProducerOwner::getLoadAdjustment(int households) {
  std::vector<int> tmp, reference;
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // if something to adjust, calculate adjustment ...
  if( stime % (24 * resolution) == 0 ) {
    // check for day
    int day = (stime / (24 * resolution)) % 7;

    // lookup reference for given day and forecast
    reference = helper::arrayToVector(referenceLoadCurves[day], 24);
    tmp = getForecastLoadCurve(households);

    // calculate difference of forecast and reference                           //TODO maybe eliminate small changes, set size to 0 if no changes
    for(unsigned i = 0; i < tmp.size(); i++) {
      tmp.at(i) -= reference.at(i);
    }

    //TODO: hier weiter... wie soll adjustment berechnet werden

    int hour = Simulation::getTime() / Simulation::getResolution();
    for (unsigned i = 0; i < tmp.size(); ++i) {
      logger->custom(Logger::toString(hour + i) + "\t" + Logger::toString(tmp.at(i) * households));
      logger2->custom(Logger::toString(hour + i) + "\t" + Logger::toString(referenceLoadCurves[day][i] * households));
    }

  } // ... else leave tmp empty ...
  return tmp;
}

/*
 *  for now return the reference load curve with a difference at hour 4 and 17
 */
std::vector<int> ProducerOwner::getForecastLoadCurve(int households) {
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();
  int day = (stime / (24 * resolution)) % 7;
  std::vector<int> tmp, baseLoad, ecoLoad, avgLoad;

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<BaseLoad> c = boost::dynamic_pointer_cast<BaseLoad>(*it)) {
      c->setWattage(getMinWattagePerHouseholdForDay(day));
      baseLoad = helper::addIntVectors(baseLoad, c->getForecastCurve(households));
    }
  }

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<Windmill> c = boost::dynamic_pointer_cast<Windmill>(*it)) {
      ecoLoad = helper::addIntVectors(ecoLoad, c->getForecastCurve(households));
    }
  }

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<AvgLoad> c = boost::dynamic_pointer_cast<AvgLoad>(*it)) {
      c->setBaseLoad(baseLoad);
      c->setExpectedLoad(helper::arrayToVector(referenceLoadCurves[day], 24));
      avgLoad = helper::addIntVectors(avgLoad, c->getForecastCurve(households));
    }
  }

  tmp = helper::addIntVectors(baseLoad, avgLoad);
  tmp = helper::addIntVectors(tmp, ecoLoad);
  return tmp;
}

int ProducerOwner::getMinWattagePerHouseholdForDay(int day) {
  int min = INT_MAX;
  for(int i=0; i < 24; i++) {
    if(referenceLoadCurves[day][i] < min) min = referenceLoadCurves[day][i];
  }
  return min;
}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

}}} /* End of namespaces */
