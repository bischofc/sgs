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

#ifndef simulation_endpoint_consumer_stove_high_h
#define simulation_endpoint_consumer_stove_high_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class StoveHigh : public Consumer {

 public:
  StoveHigh(std::string consumerId) : Consumer(consumerId) {
    int start, timeVar;
    double energy = config::EnergyPlan::getEnergyFromWattage(2500);
    int duration = config::EnergyPlan::convertTime(0,45);
    int durationVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.75) {
      start = config::EnergyPlan::convertTime(18,30);
      timeVar = config::EnergyPlan::convertTime(4);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, timeVar, durationVariation)));
    }
    if(rand > 0.5) {
      start = config::EnergyPlan::convertTime(13);
      timeVar = config::EnergyPlan::convertTime(3);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, timeVar, durationVariation)));
    }
  }

  virtual ~StoveHigh() {}
};

}}} /* End of namespaces */

#endif
