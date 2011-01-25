
#ifndef simulation_config_energyPlanStatic_h
#define simulation_config_energyPlanStatic_h

#include "energy/EnergyPlan.h"

namespace simulation {
namespace config {

class EnergyPlanStatic : public EnergyPlan {
  int nextEventTime, start, time, period, highTime, maxStartVariation, maxTimeVariation, maxHighTimeVariation;
  double currentEnergy, lowEnergy, highEnergy;
  bool running;
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
