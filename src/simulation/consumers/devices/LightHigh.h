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

#ifndef simulation_endpoint_consumer_light_high_h
#define simulation_endpoint_consumer_light_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class LightHigh : public Consumer {

public:
  LightHigh(std::string consumerId) : Consumer(consumerId) {
    int start, time, startVariation, endVariation;
    int wattage = 200;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType end = config::EnergyPlan::Endtime;
    config::EnergyPlan::TimeType duration = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(5,30);
    time = config::EnergyPlan::convertTime(8,30);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(2);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightHigh", day, end, start, time, wattage, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(18);
    time = config::EnergyPlan::convertTime(5);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(3);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightHigh", day, duration, start, time, wattage, startVariation, endVariation)));

    // in 50% of all households
    if(helper::RandomNumbers::getRandom() < 0.5) {
      start = config::EnergyPlan::convertTime(2,30);
      time = config::EnergyPlan::convertTime(4,35);
      startVariation = config::EnergyPlan::convertTime(2);
      endVariation = config::EnergyPlan::convertTime(2);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightHigh", day, end, start, time, wattage, startVariation, endVariation)));
    }
  }

  virtual ~LightHigh() {}
};

}}} /* End of namespaces */

#endif
