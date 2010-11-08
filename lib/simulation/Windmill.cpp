#include <Windmill.h>

namespace simulation {
namespace endpoint {
namespace producer {


Windmill::Windmill(std::string producerId) {
  this->id = producerId;
}

void Windmill::addEnergyPlan(config::EnergyDistributionPlan * plan) {
  std::vector<config::EnergyDistributionPlan *>::iterator it;
  it = this->energyPlans.end();
  this->energyPlans.insert(it, plan);
}

void Windmill::dump(std::ostringstream& out) {
  out << "      Producer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Windmill::getCurrentEnergy() {
  if(energyPlans.empty()) return 0.0;
  std::vector<config::EnergyDistributionPlan *>::iterator it;
  float retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
//    retVal += it->getCurrentEnergy(); //todo weiter
  }
  return (int) retVal;
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
