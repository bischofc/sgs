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


#ifndef simulation_config_energyPlanSelective_h
#define simulation_config_energyPlanSelective_h

#include "energy/EnergyPlan.h"

namespace simulation {
namespace config {

class EnergyPlanSelective : public EnergyPlan {
  const int originalStart;
  int nextEventTime, start, duration, maxStartVariation, maxDurationVariation;
  int wattage, startVariation, durationVariation, currentStart, currentEnd;
  Runtimes runtimes;
  TimeType ttype;

private:
  void updateState();
  void checkAndAdjust();
  void dump();

protected:
  bool activeInHourOnCurrentDay(int hour);

public:
  EnergyPlanSelective(const char * caller, Runtimes runtimes, TimeType ttype, int start,
                  int time, int wattage, int maxStartVariation=0,
                  int maxDurationVariation=0, bool movable=false);
  int getCurrentWattage();
  int move(int from, int to);
  bool isMovable(int from, int to);
  int getApproxStartTime();
  int getApproxRuntime();
  void reset();
  virtual ~EnergyPlanSelective() { }
};

}} /* End of namespaces */

#endif
