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

#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation, durationVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(5);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    startVariation = config::EnergyPlan::convertTime(1);
    durationVariation = config::EnergyPlan::convertTime(0,20);

    start = config::EnergyPlan::convertTime(7,0);
    duration = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Radio", day, ttype, start, duration, energy, startVariation, durationVariation)));

    start = config::EnergyPlan::convertTime(12);
    duration = config::EnergyPlan::convertTime(3,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Radio", day, ttype, start, duration, energy, startVariation, durationVariation)));

    // in 30% of all households
    if(helper::RandomNumbers::getRandom() < 0.3) {
      start = config::EnergyPlan::convertTime(2,30);
      duration = config::EnergyPlan::convertTime(4,30);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Radio", day, ttype, start, duration, energy, startVariation, durationVariation)));
    }
  }

  virtual ~Radio() {}
};

}}} /* End of namespaces */

#endif
