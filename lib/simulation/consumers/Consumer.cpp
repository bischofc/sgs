
#include "consumers/Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

Consumer::Consumer(std::string consumerId) {
  this->id = consumerId;
}

void Consumer::addEnergyPlan(config::EnergyPlan * plan) {
  this->energyPlans.push_back(plan);
}

void Consumer::dump(std::ostringstream& out) {
  out << "      Consumer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

double Consumer::getCurrentEnergy() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0.0;
  std::vector<config::EnergyPlan *>::iterator it;
  double retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += ((config::EnergyPlan *) *it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device consumes negative energy: Check you configuration file");
  return retVal;
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
