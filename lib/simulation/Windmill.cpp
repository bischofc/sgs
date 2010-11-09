#include <Windmill.h>

namespace simulation {
namespace endpoint {
namespace producer {


Windmill::Windmill(std::string producerId) {
  this->id = producerId;
}

void Windmill::addEnergyPlan(config::EnergyDistributionPlan * plan) {
  this->energyPlans.push_back(plan);
}

void Windmill::dump(std::ostringstream& out) {
  out << "      Producer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Windmill::getCurrentEnergy() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0.0;
  std::vector<config::EnergyDistributionPlan *>::iterator it;
  float retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += ((config::EnergyDistributionPlan *) *it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device produces negative energy: Check you configuration file");
  return (int) retVal;
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
