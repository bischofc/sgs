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

#ifndef simulation_endpoint_consumer_fridge_h
#define simulation_endpoint_consumer_fridge_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    int wattage = 0;
    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,10);
    int runtimeVariation = config::EnergyPlan::convertTime(0,10);

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.25) wattage = 80;
    else if(rand < 0.8) wattage = 100;
    else wattage = 170;

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod("Fridge", intervall, runtime, 0, wattage, runtimeVariation)));
  }

  virtual ~Fridge() {}
};

}}} /* End of namespaces */

#endif
