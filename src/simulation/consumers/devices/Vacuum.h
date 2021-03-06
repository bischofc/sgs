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

#ifndef simulation_endpoint_consumer_vacuum_h
#define simulation_endpoint_consumer_vacuum_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Vacuum : public Consumer {

public:
  Vacuum(std::string consumerId) : Consumer(consumerId, helper::RandomNumbers::getRandom(300,2200)) {
    config::EnergyPlan::TimeType type = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::getRandomDayOfWeek();
    int start = config::EnergyPlan::convertTime(13);
    int startVariation = config::EnergyPlan::convertTime(10);
    int duration = config::EnergyPlan::convertTime(1,5);
    int durationVariation = config::EnergyPlan::convertTime(1,50);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Vacuum", day, type, start, duration, connectedLoad, startVariation, durationVariation)));
  }

  virtual ~Vacuum() {}
};

}}} /* End of namespaces */

#endif
