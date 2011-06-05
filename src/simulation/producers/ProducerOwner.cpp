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
  if(!logger2) logger2 = Logger::getInstance("expectedLoad.log", Logger::CUSTOM);//TODO schöner machen (umbenennen oder so)
  this->id = ownerId;

  // fill the reference load curves
  // (from a previous experiment: mean per hour per household)
  std::ifstream expectedLoadFile;
  expectedLoadFile.open("./etc/expectedLoad");
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
  std::vector<int> tmp, reference;
//  std::map<int, int> overplus;
//  std::multimap<int, int> deficit;
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // if something to adjust, calculate adjustment ...
  if( stime % (24 * resolution) == 0 ) {
    // check for day
    int day = (stime / (24 * resolution)) % 7;

    // lookup reference for given day and forecast
    reference = helper::Utils::arrayToVector(referenceLoadCurves[day], 24);
    tmp = getForecastLoadCurve(households);

    // calculate difference of forecast and reference                           //TODO maybe eliminate small changes, set size to 0 if no changes
    // remember overplus times and values
    for(unsigned i = 0; i < tmp.size(); i++) {
      tmp.at(i) -= reference.at(i);
//      if(tmp.at(i) > 0) {
//        std::pair<int, int> p (i, tmp.at(i));
//        overplus.insert(p);
//      }
    }

//    deficit = getBestDeficits(reference, overplus);
//    for(std::multimap<int, int>::iterator it = deficit.begin(); it != deficit.end(); it++) {
//      if(tmp.at(it->first) > 0) throw exception::EnergyException("BUG: It is not possible to place a deficit on an overplus.");
//      tmp.at(it->first) += it->second;
//    }

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
  int dayInMonth = helper::RandomNumbers::getRandom(0, 28);//TODO

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

//std::multimap<int, int> ProducerOwner::getBestDeficits(std::vector<int> reference, std::map<int, int> overplus) { //TODO rework if needed again
//  std::multimap<int, int> tmp;
//
//  // set reference curve values at overplus times to 0
//  for(std::map<int, int>::iterator it = overplus.begin(); it != overplus.end(); it++) {
//    reference.at(it->first) = 0;
//  }
//
//  // as long as overplus exists create deficit
//  while(!overplus.empty()) {
//    // get largest values
//    std::pair<int, int> oplMax = helper::Utils::getLargestValue(overplus);
//    std::pair<int, int> refMax = helper::Utils::getLargestValue(reference);
//
//    // update reference value
//    reference.at(refMax.first) -= oplMax.second;
//
//    // add deficit to tmp
//    std::pair<int, int> p (refMax.first, -oplMax.second);                     // check here to not create another overplus
//    tmp.insert(p);
//
//    // delete overplus record
//    overplus.erase(oplMax.first);
//  }
//  return tmp;
//}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

}}} /* End of namespaces */
