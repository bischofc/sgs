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

#ifndef simulation_endpoint_consumer_fridgeMid_h
#define simulation_endpoint_consumer_fridgeMid_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class FridgeMid : public Consumer {

public:
  FridgeMid(std::string consumerId) : Consumer(consumerId, 100) {
    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,10);
    int runtimeVariation = config::EnergyPlan::convertTime(0,10);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod("Fridge", intervall, runtime, 0, connectedLoad, runtimeVariation)));
  }

  virtual ~FridgeMid() {}
};

}}} /* End of namespaces */

#endif
