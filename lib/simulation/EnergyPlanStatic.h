
#ifndef simulation_config_EnergyPlanStatic_h
#define simulation_config_EnergyPlanStatic_h

#include "Simulation.h"
#include "EnergyException.h"

namespace simulation {
namespace config {

class EnergyPlanStatic : public EnergyPlan {
  int period, highTime, lowEnergy, highEnergy;

private:
  void init(int, int, int, int, int, int);

public:
  EnergyPlanStatic(int, int, int);
  EnergyPlanStatic(int, int, int, int, int, int);
  float getCurrentEnergy();
  virtual ~EnergyPlanStatic() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_EnergyPlanStatic_h */
