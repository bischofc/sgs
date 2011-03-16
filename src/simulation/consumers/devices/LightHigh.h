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
    int start, end, startVariation, endVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(5,30);
    end = config::EnergyPlan::convertTime(8,30);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(2);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(18);
    end = config::EnergyPlan::convertTime(23,0);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    // in 50% of all households
    if(helper::RandomNumbers::getRandom() < 0.5) {
      start = config::EnergyPlan::convertTime(2,30);
      end = config::EnergyPlan::convertTime(4,30);
      startVariation = config::EnergyPlan::convertTime(2);
      endVariation = config::EnergyPlan::convertTime(2);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));
    }
  }

  virtual ~LightHigh() {}
};

}}} /* End of namespaces */

#endif
