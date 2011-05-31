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

#ifndef simulation_endpoint_consumer_computerLow_h
#define simulation_endpoint_consumer_computerLow_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerLow : public Consumer {

public:
  ComputerLow(std::string consumerId) : Consumer(consumerId, 160) {
    int start, duration, startVariation, durationVariation;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(13,30);
    startVariation = config::EnergyPlan::convertTime(2);
    duration = config::EnergyPlan::convertTime(3);
    durationVariation = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("ComputerLow", day, ttype, start, duration, connectedLoad, startVariation, durationVariation, true)));

    start = config::EnergyPlan::convertTime(19);
    startVariation = config::EnergyPlan::convertTime(4);
    duration = config::EnergyPlan::convertTime(1,30);
    durationVariation = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("ComputerLow", day, ttype, start, duration, connectedLoad, startVariation, durationVariation, true)));
  }

  virtual ~ComputerLow() {}
};

}}} /* End of namespaces */

#endif
