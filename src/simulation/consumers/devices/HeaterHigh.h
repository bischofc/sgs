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

#ifndef simulation_endpoint_consumer_heater_high_h
#define simulation_endpoint_consumer_heater_high_h

#include "energy/plans/EnergyPlanSelectivePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class HeaterHigh : public Consumer {

 public:
  HeaterHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double hEnergy = config::EnergyPlan::getEnergyFromWattage(300);
    double lEnergy = config::EnergyPlan::getEnergyFromWattage(50);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int intervall = config::EnergyPlan::convertTime(1);
    int hightime = config::EnergyPlan::convertTime(0,20);
    int startVariation = config::EnergyPlan::convertTime(1,30);
    int durationVariation = config::EnergyPlan::convertTime(0,20);

    start = config::EnergyPlan::convertTime(6,0);
    end = config::EnergyPlan::convertTime(22,45);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod("HeaterHigh", day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, startVariation, durationVariation)));

    // in 20% of all households
    if(helper::RandomNumbers::getRandom() < 0.2) {
      start = config::EnergyPlan::convertTime(2,30);
      end = config::EnergyPlan::convertTime(4,30);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod("HeaterHigh", day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, startVariation, durationVariation)));
    }
  }

  virtual ~HeaterHigh() {}
};

}}} /* End of namespaces */

#endif
