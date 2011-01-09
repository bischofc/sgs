
#ifndef simulation_config_energyPlanStatic_h
#define simulation_config_energyPlanStatic_h

#include "energy/EnergyPlan.h"

namespace simulation {
namespace config {

class EnergyPlanStatic : public EnergyPlan {
  int start, end, period, highTime;
  double lowEnergy, highEnergy;

private:
  void init(int, int, int, int, double, double);

public:
  EnergyPlanStatic(int, int, double);
  EnergyPlanStatic(int, int, int, int, double, double);
  double getCurrentEnergy();
  virtual ~EnergyPlanStatic() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_energyPlanStatic_h */