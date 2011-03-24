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
  int tmp1[24] = {131, 150, 203, 251, 223, 312, 419, 413, 540, 695, 770, 746, 818, 734, 635, 538, 685,  961, 1007, 1029, 905, 619, 420, 151};
  int tmp2[24] = {136, 148, 204, 248, 224, 309, 416, 413, 528, 704, 777, 754, 836, 755, 641, 537, 689,  980, 1027, 1049, 901, 611, 420, 151};
  int tmp3[24] = {137, 149, 204, 251, 221, 313, 416, 412, 544, 715, 779, 757, 838, 759, 656, 558, 698,  983, 1034, 1041, 919, 622, 421, 152};
  int tmp4[24] = {135, 151, 207, 250, 224, 309, 419, 411, 531, 694, 754, 717, 786, 710, 642, 551, 692,  960, 1012, 1038, 896, 614, 418, 150};
  int tmp5[24] = {137, 147, 205, 250, 223, 313, 416, 414, 531, 699, 768, 753, 815, 709, 642, 549, 685,  989, 1052, 1060, 912, 619, 422, 151};
  int tmp6[24] = {135, 149, 202, 250, 223, 311, 416, 417, 552, 746, 870, 897, 984, 928, 831, 765, 931, 1202, 1109, 1037, 892, 606, 414, 152};
  int tmp7[24] = {136, 147, 204, 248, 224, 311, 417, 417, 547, 736, 882, 900, 984, 894, 829, 768, 942, 1222, 1106, 1053, 898, 605, 420, 150};
  for(int i = 0; i < 24; i++) referenceLoadCurves[0][i] = tmp1[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[1][i] = tmp2[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[2][i] = tmp3[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[3][i] = tmp4[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[4][i] = tmp5[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[5][i] = tmp6[i];
  for(int i = 0; i < 24; i++) referenceLoadCurves[6][i] = tmp7[i];
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
std::vector<int> ProducerOwner::getForecastLoadCurve(int households) {          //TODO do some magic here, make sure it's per household
  int stime = Simulation::getTime();
  int resolution = Simulation::getResolution();

  // get reference load for current day
  int day = (stime / (24 * resolution)) % 7;
  std::vector<int> tmp = helper::Utils::arrayToVector(referenceLoadCurves[day], 24);

  // change values
//  tmp.at(2) += 5;
//  tmp.at(9) -= 1;
//  tmp.at(11) -= 1;
//  tmp.at(13) -= 1;
//  tmp.at(15) -= 1;
//  tmp.at(17) -= 1;
  return tmp;
}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

}}} /* End of namespaces */
