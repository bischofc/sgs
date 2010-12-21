
#ifndef simulation_config_energyDistributionPlan_h
#define simulation_config_energyDistributionPlan_h

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

#endif /* simulation_config_energyDistributionPlan_h */
