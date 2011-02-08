
#ifndef simulation_config_energyPlan_h
#define simulation_config_energyPlan_h

#include "exceptions/EnergyException.h"

namespace simulation {
namespace config {

class EnergyPlan {

protected:
  EnergyPlan() {}

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
  static double getEnergyFromWattage(double wattage);
  static int convertTime(int hour, int minute=0);

  static int getTimeOnCurrentDay();
  static int getTimeInWeekForDay(Runtimes day);
  static int getAbsTimeOfNextRuntimeDay(Runtimes runtimes);
  static int getVariation(int maxVariation);

  static Runtimes getDayOfTheWeek();
  static Runtimes getNextDayOfWeek(Runtimes day);
  static Runtimes shiftDay(Runtimes day, int shift=1);
  static Runtimes getFirstDayInRunTimes(Runtimes runtimes);
  static Runtimes getRandomDayOfWeek();


public:
  virtual double getCurrentEnergy() =0;
  virtual ~EnergyPlan() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_energyPlan_h */
