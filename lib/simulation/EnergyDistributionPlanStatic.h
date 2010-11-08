
#ifndef ENERGYDISTRIBUTIONPLANSTATIC_H_
#define ENERGYDISTRIBUTIONPLANSTATIC_H_

#include <EnergyDistributionPlan.h>

namespace simulation {
namespace config {

class EnergyDistributionPlanStatic : public EnergyDistributionPlan {
  int rate;

public:
  EnergyDistributionPlanStatic(int rate);
  float getCurrentEnergy();
  virtual ~EnergyDistributionPlanStatic() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* ENERGYDISTRIBUTIONPLANSTATIC_H_ */
