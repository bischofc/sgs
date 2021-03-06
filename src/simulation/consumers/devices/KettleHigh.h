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

#ifndef simulation_endpoint_consumer_kettle_high_h
#define simulation_endpoint_consumer_kettle_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class KettleHigh : public Consumer {

 public:
  KettleHigh(std::string consumerId) : Consumer(consumerId, 2000) {
    int start;
    int startVariation = config::EnergyPlan::convertTime(1);
    int duration = config::EnergyPlan::convertTime(0,4);
    int durationVariation = config::EnergyPlan::convertTime(0,4);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    for(int i=0; i<helper::RandomNumbers::getRandom(2,7); i++) {
      start = config::EnergyPlan::convertTime(helper::RandomNumbers::getRandom(0,23),30);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("KettleHigh", day, ttype, start, duration, connectedLoad, startVariation, durationVariation)));
    }
  }

  virtual ~KettleHigh() {}
};

}}} /* End of namespaces */

#endif
