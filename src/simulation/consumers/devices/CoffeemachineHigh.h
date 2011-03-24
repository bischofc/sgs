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

#ifndef simulation_endpoint_consumer_coffeemachine_high_h
#define simulation_endpoint_consumer_coffeemachine_high_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class CoffeemachineHigh : public Consumer {

public:
  CoffeemachineHigh(std::string consumerId) : Consumer(consumerId) {
    int start;
    int wattage = 1000;
    int duration = config::EnergyPlan::convertTime(0,7);
    int startVariation = config::EnergyPlan::convertTime(3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(3,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineHigh", day, ttype, start, duration, wattage, startVariation)));

    start = config::EnergyPlan::convertTime(6);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineHigh", day, ttype, start, duration, wattage, startVariation)));

    // in 15% of all households
    if(helper::RandomNumbers::getRandom() < 0.15) {
      start = config::EnergyPlan::convertTime(13);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineHigh", day, ttype, start, duration, wattage, startVariation)));
    }

    start = config::EnergyPlan::convertTime(17,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineHigh", day, ttype, start, duration, wattage, startVariation)));
  }

  virtual ~CoffeemachineHigh() {}
};

}}} /* End of namespaces */

#endif
