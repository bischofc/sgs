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

#ifndef simulation_endpoint_consumer_washer_low_h
#define simulation_endpoint_consumer_washer_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class WasherLow : public Consumer {

 public:
  WasherLow(std::string consumerId) : Consumer(consumerId, 450) {
    int start = config::EnergyPlan::convertTime(13);
    int startVariation = config::EnergyPlan::convertTime(8);
    int duration = config::EnergyPlan::convertTime(3);
    int durationVariation = config::EnergyPlan::convertTime(1);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    config::EnergyPlan::Runtimes day;

    if(helper::RandomNumbers::getRandom() < 0.5) day = config::EnergyPlan::Sat;
    else day = config::EnergyPlan::Sun;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("WasherLow", day, ttype, start, duration, connectedLoad, startVariation, durationVariation, true)));
  }

  virtual ~WasherLow() {}
};

}}} /* End of namespaces */

#endif
