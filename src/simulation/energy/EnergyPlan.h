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


#ifndef simulation_config_energyPlan_h
#define simulation_config_energyPlan_h

#include "exceptions/EnergyException.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlan {

protected:
  static boost::shared_ptr<Logger> logger;
  bool movable;
  int currentWattage;
  const std::string holderName;

public:
  enum Runtimes {
    Mon       = 0x01,
    Tue       = 0x02,
    Wed       = 0x04,
    Thu       = 0x08,
    Fri       = 0x10,
    Weekdays  = 0x1f,                                                           // short for: Mon|Tue|Wed|Thu|Fri
    Sat       = 0x20,
    Sun       = 0x40,
    Weekend   = 0x60,                                                           // short for: Sat|Sun
    Alldays   = 0x7f                                                            // short for: Mon|Tue|Wed|Thu|Fri|Sat|Sun
  };
  enum TimeType { Off, Endtime, Duration };

public:                                                                         // TODO protected?
  static int convertTime(int hour, int minute=0);

  static int getTimeOnCurrentDay();
  static int getTimeOfCurrentDay();
  static int getTimeInWeekForDay(Runtimes day);
  static int getAbsTimeOfNextRuntimeDay(Runtimes runtimes);
  static int getVariation(int maxVariation);

  static Runtimes getDayOfTheWeek();
  static Runtimes getNextDayOfWeek(Runtimes day);
  static Runtimes shiftDay(Runtimes day, int shift=1);
  static Runtimes getFirstDayInRunTimes(Runtimes runtimes);
  static Runtimes getRandomDayOfWeek();

protected:
  EnergyPlan(std::string holder, bool movable);
  virtual bool activeInHourOnCurrentDay(int hour) =0;

public:
  virtual int getCurrentWattage() =0;
  virtual void move(int from, int to) =0;
  virtual void reset() =0;
  virtual ~EnergyPlan() { }
};

}} /* End of namespaces */

#endif
