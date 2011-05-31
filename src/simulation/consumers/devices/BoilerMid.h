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

#ifndef simulation_endpoint_consumer_boiler_mid_h
#define simulation_endpoint_consumer_boiler_mid_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class BoilerMid : public Consumer {

public:
  BoilerMid(std::string consumerId) : Consumer(consumerId, 2000) {
    int period = config::EnergyPlan::convertTime(5);
    int duration = config::EnergyPlan::convertTime(0,30);
    int highTimeVariation = config::EnergyPlan::convertTime(0,10);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod("BoilerMid", period, duration, 0, connectedLoad, highTimeVariation)));
  }

  virtual ~BoilerMid() {}
};

}}} /* End of namespaces */

#endif
