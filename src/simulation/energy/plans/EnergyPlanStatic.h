
#ifndef simulation_config_energyPlanStatic_h
#define simulation_config_energyPlanStatic_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanStatic : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  int nextEventTime, start, time, period, highTime, maxStartVariation, maxTimeVariation, maxHighTimeVariation;
  int startVariation, timeVariation, highTimeVariation;
  double currentEnergy, lowEnergy, highEnergy;
  Runtimes runtimes;
  TimeType ttype;

private:
  void init(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int msv, int mtv, int mhtv);
  void updateState();

public:
  EnergyPlanStatic(double energy);
  EnergyPlanStatic(int period, int highTime, double lowEnergy, double highEnergy,
                  int maxHighTimeVariation=0);
  EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, double energy,
                  int maxStartVariation=0, int maxTimeVariation=0);
  EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy,
                  int maxStartVariation=0, int maxTimeVariation=0, int maxHighTimeVariation=0);
  double getCurrentEnergy();
  virtual ~EnergyPlanStatic() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_energyPlanStatic_h */
