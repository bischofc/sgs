
#ifndef simulation_config_EnergyDistributionPlanStatic_h
#define simulation_config_EnergyDistributionPlanStatic_h

#include "Simulation.h"

namespace simulation {
namespace config {

class EnergyDistributionPlanStatic : public EnergyDistributionPlan {
  int rate;

public:
  EnergyDistributionPlanStatic(int, int, int);
  float getCurrentEnergy();
  virtual ~EnergyDistributionPlanStatic() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_EnergyDistributionPlanStatic_h */
