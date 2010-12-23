
#include "Consumer.h"
#include "EnergyPlanFactory.h"  //TODO herausfinden warum ich das nicht in Consumer.h schieben kann

namespace simulation {
namespace endpoint {
namespace consumer {

Consumer::Consumer(std::string consumerId) {
  this->id = consumerId;
}

void Consumer::addEnergyPlan(config::EnergyPlan * plan) {
  this->energyPlans.push_back(plan);
}

config::EnergyPlan * Consumer::getBasicEnergyPlan(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
  // set energy parameters and return energy plan
  std::map<std::string, int> params;
  std::pair<std::string, int> s ("start", start); params.insert(s);
  std::pair<std::string, int> e ("end", end); params.insert(e);
  std::pair<std::string, int> p ("period", period); params.insert(p);
  std::pair<std::string, int> ht ("highTime", highTime); params.insert(ht);
  std::pair<std::string, int> le ("lowEnergy", lowEnergy); params.insert(le);
  std::pair<std::string, int> he ("highEnergy", highEnergy); params.insert(he);
  return config::EnergyPlanFactory::getInstance("static", params);
}

void Consumer::dump(std::ostringstream& out) {
  out << "      Consumer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Consumer::getCurrentEnergy() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0.0;
  std::vector<config::EnergyPlan *>::iterator it;
  float retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += ((config::EnergyPlan *) *it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device consumes negative energy: Check you configuration file");
  return (int) retVal;
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
