
#ifndef ENERGYDISTRIBUTIONPLANSTATIC_H_
#define ENERGYDISTRIBUTIONPLANSTATIC_H_

#include <Simulation.h>

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

#endif /* ENERGYDISTRIBUTIONPLANSTATIC_H_ */
