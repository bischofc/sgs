
#include "Producer.h"
#include "Simulation.h"

namespace simulation {
namespace endpoint {
namespace producer {

/**
 * Set id here and further parameters in constructor of subclass
 */
Producer::Producer(std::string producerId) {
  this->id = producerId;
  this->running = false;
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

void Producer::addEnergyPlan(boost::shared_ptr<config::EnergyPlan> plan) {
  this->energyPlans.push_back(plan);
}

void Producer::dump(std::ostringstream& out) {
  out << "      Producer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

double Producer::getCurrentEnergy() throw (exception::EnergyException) {
  // no energy plan, not running or within startup time -> no energy
  if(energyPlans.empty()) return 0.0;
  if(!running) return 0.0;
  if(running && Simulation::getTime() - startupTime < startTime) return 0.0;

  // up and running -> energy
  std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it;
  double retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += (*it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device produces negative energy: Check you configuration file");
  return retVal;
}

int Producer::getStartupTime() {
  return startupTime;
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */