
#ifndef simulation_config_EnergyDistributionPlanFactory_h
#define simulation_config_EnergyDistributionPlanFactory_h

#include <string>
#include <sstream>
#include <map>

#include "NoSuchEnergyPlanException.h"
#include "EnergyDistributionPlanStatic.h"
#include "EnergyDistributionPlanRepeat.h"

namespace simulation {
namespace config {

class EnergyDistributionPlanFactory {
  EnergyDistributionPlanFactory();

public:
  static EnergyDistributionPlan * getInstance(std::string type, std::map<std::string, std::string>) throw (exception::NoSuchEnergyPlanException);
  virtual ~EnergyDistributionPlanFactory();
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_EnergyDistributionPlanFactory_h */
