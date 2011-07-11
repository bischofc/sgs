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
#include <algorithm>
#include "ProducerOwner.h"
#include "DeviceFactory.h"
#include "Simulation.h"
#include "Utils.h"
#include "RandomNumbers.h"
#include "exceptions/IOException.h"

#include "devices/Conventional.h"
#include "devices/Solar.h"
#include "devices/Windmill.h"

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  if(!logger) logger = Logger::getInstance("adjustment.log", Logger::CUSTOM);
  if(!logger2) logger2 = Logger::getInstance("expectedLoad.log", Logger::CUSTOM);
  this->id = ownerId;

  // fill the reference load curves
  // (from a previous experiment: mean per hour per household)
  std::ifstream expectedLoadFile;
  expectedLoadFile.open("./etc/data/expectedLoad");
  if(expectedLoadFile.fail()) throw exception::IOException("file not found");
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
  std::vector<int> tmp;
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // if something to adjust, calculate adjustment ...
  if( stime % (24 * resolution) == 0 ) {
    std::vector<int> reference;

    // check for day
    int day = (stime / (24 * resolution)) % 7;

    // lookup reference for given day and forecast
    reference = helper::Utils::arrayToVector(referenceLoadCurves[day], 24);
    tmp = getForecastLoadCurve(households);

    // calculate difference of forecast and reference                           //TODO maybe eliminate small changes
    for(unsigned i = 0; i < tmp.size(); i++) {
      tmp.at(i) -= reference.at(i);
    }

    addBestDeficits(reference, tmp);

    int hour = stime / Simulation::getResolution();
    for (unsigned i = 0; i < tmp.size(); ++i) {
      logger->custom(Logger::toString(hour + i) + "\t" + Logger::toString(tmp.at(i) * households));
      logger2->custom(Logger::toString(hour + i) + "\t" + Logger::toString(referenceLoadCurves[day][i] * households));
    }

  } // ... else leave tmp empty ...
  return tmp;
}

std::vector<int> ProducerOwner::getForecastLoadCurve(int households) {
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();
  int day = (stime / (24 * resolution)) % 7;
  std::vector<int> tmp, convLoad, solarLoad, windLoad;
  int dayInMonth = helper::RandomNumbers::getRandom(0, 29);

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<Solar> c = boost::dynamic_pointer_cast<Solar>(*it)) {
      c->setExpectedLoad(helper::Utils::arrayToVector(referenceLoadCurves[day], 24));
      solarLoad = helper::Utils::addIntVectors(solarLoad, c->getForecastCurve(households, dayInMonth));
    }
  }

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<Windmill> c = boost::dynamic_pointer_cast<Windmill>(*it)) {
      c->setExpectedLoad(helper::Utils::arrayToVector(referenceLoadCurves[day], 24));
      windLoad = helper::Utils::addIntVectors(windLoad, c->getForecastCurve(households, dayInMonth));
    }
  }

  for(std::vector< boost::shared_ptr<Producer> >::iterator it = producerList.begin();
      it != producerList.end(); it++) {
    if(boost::shared_ptr<Conventional> c = boost::dynamic_pointer_cast<Conventional>(*it)) {
      c->setExpectedLoad(helper::Utils::arrayToVector(referenceLoadCurves[day], 24));
      convLoad = helper::Utils::addIntVectors(convLoad, c->getForecastCurve(households, dayInMonth));
    }
  }

  tmp = helper::Utils::addIntVectors(solarLoad, windLoad);
  tmp = helper::Utils::addIntVectors(tmp, convLoad);
  return tmp;
}

void ProducerOwner::addBestDeficits(const std::vector<int> &reference, std::vector<int> &adjustment) {
  std::vector<int> tmpReference = reference;
  int overplus = 0;
  // set reference curve values at overplus times to 0
  for(unsigned i = 0; i < adjustment.size(); i++) {
    overplus += adjustment[i];
    if(adjustment[i] > 0) tmpReference[i] = 0;
  }

  // as long as total overplus > 0, create more deficit
  while(overplus > 0) {
    // get largest reference value, return if == 0
    std::pair<int, int> refMax = helper::Utils::getLargestValue(tmpReference);
    if(refMax.second == 0) return;

    // update reference value, adjustment and total overplus                    // check here to not create another overplus
    int red = std::min(std::min(overplus, refMax.second), 10);
    tmpReference[refMax.first] -= red;
    adjustment[refMax.first] -= red;
    overplus -= red;
  }
}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

}}} /* End of namespaces */
