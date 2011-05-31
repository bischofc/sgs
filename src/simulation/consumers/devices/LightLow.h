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

#ifndef simulation_endpoint_consumer_light_low_h
#define simulation_endpoint_consumer_light_low_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class LightLow : public Consumer {

public:
  LightLow(std::string consumerId) : Consumer(consumerId, 200) {
    int start, end, startVariation, endVariation;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(5,30);
    end = config::EnergyPlan::convertTime(8,30);
    startVariation = config::EnergyPlan::convertTime(1);
    endVariation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightLow", day, ttype, start, end, connectedLoad, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(18);
    end = config::EnergyPlan::convertTime(22,45);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(1);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightLow", day, ttype, start, end, connectedLoad, startVariation, endVariation)));

    // in 30% of all households
    if(helper::RandomNumbers::getRandom() < 0.5) {
      start = config::EnergyPlan::convertTime(2,30);
      end = config::EnergyPlan::convertTime(4,35);
      startVariation = config::EnergyPlan::convertTime(2);
      endVariation = config::EnergyPlan::convertTime(2);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("LightLow", day, ttype, start, end, connectedLoad, startVariation, endVariation)));
    }
  }

  virtual ~LightLow() {}
};

}}} /* End of namespaces */

#endif
