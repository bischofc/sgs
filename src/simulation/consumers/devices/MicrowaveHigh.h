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

#ifndef simulation_endpoint_consumer_microwave_high_h
#define simulation_endpoint_consumer_microwave_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class MicrowaveHigh : public Consumer {

 public:
  MicrowaveHigh(std::string consumerId) : Consumer(consumerId, 1000) {
    int start, duration, startVariation, durationVariation;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    startVariation = config::EnergyPlan::convertTime(2);
    duration = config::EnergyPlan::convertTime(0,4);
    durationVariation = config::EnergyPlan::convertTime(0,4);

    if(helper::RandomNumbers::getRandom() < 0.5) start = config::EnergyPlan::convertTime(12);
    else start = config::EnergyPlan::convertTime(18,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("MicrowaveHigh", day, ttype, start, duration, connectedLoad, startVariation, durationVariation)));

    if(helper::RandomNumbers::getRandom() < 0.5) start = config::EnergyPlan::convertTime(2);
    else start = config::EnergyPlan::convertTime(20);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("MicrowaveHigh", day, ttype, start, duration, connectedLoad, startVariation, durationVariation)));
  }

  virtual ~MicrowaveHigh() {}
};

}}} /* End of namespaces */

#endif
