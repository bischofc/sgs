#include <Fridge.h>

namespace simulation {
namespace endpoint {
namespace consumer {


Fridge::Fridge(std::string consumerId) {
  this->id = consumerId;
}

void Fridge::addEnergyPlan(config::EnergyDistributionPlan * plan) {
  this->energyPlans.push_back(plan);
}

void Fridge::dump(std::ostringstream& out) {
  out << "      Consumer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Fridge::getCurrentEnergy() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0.0;
  std::vector<config::EnergyDistributionPlan *>::iterator it;
  float retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += ((config::EnergyDistributionPlan *) *it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device consumes negative energy: Check you configuration file");
  return (int) retVal;
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
