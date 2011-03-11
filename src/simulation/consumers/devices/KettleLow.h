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

#ifndef simulation_endpoint_consumer_kettle_low_h
#define simulation_endpoint_consumer_kettle_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class KettleLow : public Consumer {

 public:
  KettleLow(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int startVariation = config::EnergyPlan::convertTime(1);
    int duration = config::EnergyPlan::convertTime(0,4);
    int durationVariation = config::EnergyPlan::convertTime(0,4);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    for(int i=0; i<helper::RandomNumbers::getRandom(1,4); i++) {
      start = config::EnergyPlan::convertTime(helper::RandomNumbers::getRandom(7,22));
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
    }
  }

  virtual ~KettleLow() {}
};

}}} /* End of namespaces */

#endif
