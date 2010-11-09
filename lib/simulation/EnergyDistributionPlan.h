
#ifndef ENERGYDISTRIBUTIONPLAN_H_
#define ENERGYDISTRIBUTIONPLAN_H_

namespace simulation {
namespace config {

class EnergyDistributionPlan {
protected:
  int start;
  int end;

public:
  virtual float getCurrentEnergy() =0;
  virtual ~EnergyDistributionPlan() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* ENERGYDISTRIBUTIONPLAN_H_ */
