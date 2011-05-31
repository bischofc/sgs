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

#ifndef simulation_endpoint_consumer_dishwasher_high_h
#define simulation_endpoint_consumer_dishwasher_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class DishwasherHigh : public Consumer {

public:
  DishwasherHigh(std::string consumerId) : Consumer(consumerId, 300) {
    int start;
    int duration = config::EnergyPlan::convertTime(3);
    int startVariation = config::EnergyPlan::convertTime(2);
    int durationVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.5) start = config::EnergyPlan::convertTime(13);
    else start = config::EnergyPlan::convertTime(19,00);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("DishwasherHigh", day, ttype, start, duration, connectedLoad, startVariation, durationVariation, true)));
  }

  virtual ~DishwasherHigh() {}
};

}}} /* End of namespaces */

#endif
