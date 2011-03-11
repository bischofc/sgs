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


#ifndef simulation_config_energyPlanInfinitePeriod_h
#define simulation_config_energyPlanInfinitePeriod_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanInfinitePeriod : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  int nextEventTime, period, highTime, offset, maxHighTimeVariation, highTimeVariation;
  double currentEnergy, lowEnergy, highEnergy;

private:
  void updateState();

public:
  EnergyPlanInfinitePeriod(int period, int highTime, double lowEnergy, double highEnergy,
                  int maxHighTimeVariation=0);
  double getCurrentEnergy();
  virtual ~EnergyPlanInfinitePeriod() { }
};

}} /* End of namespaces */

#endif
