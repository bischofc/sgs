
#ifndef ENERGYDISTRIBUTIONPLANFACTORY_H_
#define ENERGYDISTRIBUTIONPLANFACTORY_H_

#include <NoSuchEnergyPlanException.h>
#include <EnergyDistributionPlan.h>
#include <EnergyDistributionPlanStatic.h>
#include <EnergyDistributionPlanRepeat.h>
#include <string>
#include <sstream>
#include <map>

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

#endif /* ENERGYDISTRIBUTIONPLANFACTORY_H_ */
