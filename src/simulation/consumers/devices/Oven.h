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

#ifndef simulation_endpoint_consumer_oven_h
#define simulation_endpoint_consumer_oven_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Oven : public Consumer {

 public:
  Oven(std::string consumerId) : Consumer(consumerId, 2000) {
    config::EnergyPlan::Runtimes day = config::EnergyPlan::getRandomDayOfWeek();
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    int startVariation = config::EnergyPlan::convertTime(2,30);
    int durationVariation = config::EnergyPlan::convertTime(0,45);
    int duration = config::EnergyPlan::convertTime(2,15);

    int start;
    if(helper::RandomNumbers::getRandom() < 0.5) start = config::EnergyPlan::convertTime(11,30);
    else start = config::EnergyPlan::convertTime(17,30);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Oven", day, ttype, start, duration, connectedLoad, startVariation, durationVariation)));
  }

  virtual ~Oven() {}
};

}}} /* End of namespaces */

#endif
