
#include "Producer.h"
#include "Simulation.h"  //TODO herausfinden warum ich das nicht in Producer.h schieben kann
#include "EnergyPlanFactory.h"   //TODO herausfinden warum ich das nicht in Producer.h schieben kann

namespace simulation {
namespace endpoint {
namespace producer {

/**
 * Set id here and further parameters in constructor of subclass
 */
Producer::Producer(std::string producerId) {
  this->id = producerId;
}

/**
 * @instant: if true turns on the windmill instantly i.e. without startup time
 *           e.g. used to get energy directly at time 0;
*/
void Producer::activate(bool instant) { //:TODO: was aktivieren?
  //TODO: if running write to log!
  if(!running) {
    startTime = Simulation::getTime();
    if(instant) startTime -= startupTime;
  }
  running = true;
}

void Producer::deactivate() { //TODO: was deaktivieren?
  //TODO: if !running write to log!
  //TODO: was wenn deaktiviert, wenn grade aktiviert wird?
  running = false;
}

void Producer::addEnergyPlan(config::EnergyPlan * plan) {
  this->energyPlans.push_back(plan);
}

config::EnergyPlan * Producer::getBasicEnergyPlan(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
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

void Producer::dump(std::ostringstream& out) {
  out << "      Producer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Producer::getCurrentEnergy() throw (exception::EnergyException) {
  // no energy plan, not running or within startup time -> no energy
  if(energyPlans.empty()) return 0.0;
  if(!running) return 0.0;
  if(running && Simulation::getTime() - startupTime < startTime) return 0.0;

  // up and running -> energy
  std::vector<config::EnergyPlan *>::iterator it;
  float retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += ((config::EnergyPlan *) *it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device produces negative energy: Check you configuration file");
  return (int) retVal;
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
