
#ifndef simulation_config_energyPlan_h
#define simulation_config_energyPlan_h

namespace simulation {
namespace config {

class EnergyPlan {

public:
  static int getEnergyFromWattage(int wattage);

  virtual float getCurrentEnergy() =0;
  virtual ~EnergyPlan() { }
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_energyPlan_h */
