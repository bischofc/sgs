
#ifndef simulation_config_EnergyPlanFactory_h
#define simulation_config_EnergyPlanFactory_h

#include <string>
#include <sstream>
#include <map>

#include "NoSuchEnergyPlanException.h"
#include "EnergyPlanStatic.h"
#include "EnergyPlanDynamic.h"

namespace simulation {
namespace config {

class EnergyPlanFactory {
  EnergyPlanFactory();

public:
  static EnergyPlan * getInstance(std::string type, std::map<std::string, int>) throw (exception::NoSuchEnergyPlanException);
  virtual ~EnergyPlanFactory();
};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif /* simulation_config_EnergyPlanFactory_h */
