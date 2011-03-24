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

#ifndef simulation_endpoint_consumer_television_high_h
#define simulation_endpoint_consumer_television_high_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class TelevisionHigh : public Consumer {

 public:
  TelevisionHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end, startVariation, endVariation;
    int wattage = helper::RandomNumbers::getRandom(90,200);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    config::EnergyPlan::Runtimes day;

    start = config::EnergyPlan::convertTime(19);
    startVariation = config::EnergyPlan::convertTime(2);
    end = config::EnergyPlan::convertTime(22,30);
    endVariation = config::EnergyPlan::convertTime(2);
    day = config::EnergyPlan::Alldays;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("TelevisionHigh", day, ttype, start, end, wattage, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(15);
    startVariation = config::EnergyPlan::convertTime(4);
    end = config::EnergyPlan::convertTime(18,5);
    endVariation = config::EnergyPlan::convertTime(2);
    day = config::EnergyPlan::Alldays;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("TelevisionHigh", day, ttype, start, end, wattage, startVariation, endVariation)));

    // in 7% of the households
    if(helper::RandomNumbers::getRandom() < 0.07) {
      start = config::EnergyPlan::convertTime(2);
      startVariation = config::EnergyPlan::convertTime(1);
      end = config::EnergyPlan::convertTime(5);
      endVariation = config::EnergyPlan::convertTime(1);
      day = config::EnergyPlan::Alldays;
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("TelevisionHigh", day, ttype, start, end, wattage, startVariation, endVariation)));
    }
  }

  virtual ~TelevisionHigh() {}
};

}}} /* End of namespaces */

#endif
