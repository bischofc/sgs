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

#include "ProducerOwner.h"
#include "DeviceFactory.h"
#include "Simulation.h"
#include "Utils.h"

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  this->id = ownerId;

  // fill the reference load curves
  // (from a previous experiment: mean per hour per household)
  referenceLoadCurves[0] = {2.58, 2.44, 3.23, 4.14, 3.74, 5.51, 6.90, 6.49, 9.31, 10.61, 10.38,  9.75, 13.74, 11.73, 11.95,  9.91, 11.15, 14.55, 17.76, 16.14, 16.71, 10.68, 6.73, 2.34};
  referenceLoadCurves[1] = {2.60, 3.09, 3.58, 3.72, 3.36, 5.46, 7.47, 6.41, 8.48, 11.05, 11.99, 11.83, 14.94, 14.67, 13.53, 10.87, 11.92, 15.63, 17.24, 17.93, 15.09, 11.48, 6.87, 1.97};
  referenceLoadCurves[2] = {2.24, 2.87, 4.11, 3.96, 3.04, 5.32, 7.24, 7.43, 9.09,  9.87, 11.39, 11.32, 15.79, 13.86, 11.21,  9.29, 12.60, 15.54, 18.19, 17.27, 15.30, 11.34, 7.40, 2.19};
  referenceLoadCurves[3] = {1.79, 2.57, 4.15, 4.81, 3.23, 4.67, 6.91, 6.80, 9.35, 10.34, 10.35,  9.09, 13.38, 13.26, 11.32,  9.83, 11.90, 15.23, 17.39, 15.96, 15.89, 10.86, 7.56, 2.82};
  referenceLoadCurves[4] = {2.15, 2.08, 3.57, 4.50, 3.82, 5.00, 6.39, 6.81, 9.15, 11.13, 10.78, 10.60, 12.80, 14.06, 10.43,  9.04, 10.98, 14.40, 18.27, 16.70, 16.05, 10.21, 7.07, 2.70};
  referenceLoadCurves[5] = {2.69, 2.49, 3.41, 4.13, 3.77, 5.56, 6.83, 6.22, 8.96, 13.16, 15.25, 13.77, 14.69, 14.88, 15.61, 13.66, 14.53, 17.86, 18.03, 18.26, 13.64, 10.49, 6.39, 2.33};
  referenceLoadCurves[6] = {2.62, 3.11, 3.57, 3.79, 3.49, 5.29, 7.62, 6.75, 9.04, 11.13, 12.34, 14.44, 17.08, 14.21, 15.50, 13.54, 15.52, 19.34, 19.10, 16.77, 15.73, 10.83, 7.01, 2.00};
}

std::string ProducerOwner::getId() {
  return 0;
}

// returns an empty vector if no adjustment is necessary
// otherwise a vector with 24 elements
std::vector<double> ProducerOwner::getLoadAdjustment(int households) {
  std::vector<double> tmp, reference;
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // if something to adjust, calculate adjustment ...
  if( stime % (24 * resolution) == 0 ) {
    // check for day
    int day = (stime / (24 * resolution)) % 7;

    // lookup reference for given day and forecast
    reference = helper::Utils::arrayToVector(referenceLoadCurves[day], 24);
    tmp = getForecastLoadCurve(households);

    // calculate difference of forecast and difference                          //TODO maybe eliminate small changes, set size to 0 if no changes
    for(unsigned i = 0; i < tmp.size(); i++) {
      tmp.at(i) -= reference.at(i);
    }
  } // ... else leave tmp empty ...

  // ... and return tmp
  return tmp;
}

/*
 *  for now return the reference load curve with a difference at hour 4 and 17
 */
std::vector<double> ProducerOwner::getForecastLoadCurve(int households) {       //TODO do some magic here, make sure it's per household
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // get reference load for current day
  int day = (stime / (24 * resolution)) % 7;
  std::vector<double> tmp = helper::Utils::arrayToVector(referenceLoadCurves[day], 24);

  // change values
  tmp.at(2) += 5;
  tmp.at(9) -= 1;
  tmp.at(11) -= 1;
  tmp.at(13) -= 1;
  tmp.at(15) -= 1;
  tmp.at(17) -= 1;
  return tmp;
}

void ProducerOwner::dump(std::ostringstream &out) {
  out << "    ProducerOwner-Id: " << this->id << std::endl;
  for(std::vector< boost::shared_ptr<Producer> >::iterator it = this->producerList.begin();
      it != this->producerList.end(); it++) {
    (*it)->dump(out);
  }
}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

}}} /* End of namespaces */
