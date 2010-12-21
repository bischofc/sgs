#include <Windmill.h>

namespace simulation {
namespace endpoint {
namespace producer {


Windmill::Windmill(std::string producerId) {
  this->id = producerId;

  // build windmill behavior
  startupTime = 3;
  std::map<std::string, std::string> params;
  std::pair<std::string, std::string> start ("start", "-1");
  params.insert(start);
  std::pair<std::string, std::string> end ("end", "-1");
  params.insert(end);
  std::pair<std::string, std::string> rate ("rate", "100");
  params.insert(rate);
  config::EnergyDistributionPlan * plan = config::EnergyDistributionPlanFactory::getInstance("static", params);
  addEnergyPlan(plan);

  // start windmill
  activate(true);
}

void Windmill::addEnergyPlan(config::EnergyDistributionPlan * plan) {
  this->energyPlans.push_back(plan);
}

/**
 * Inherited from Producer
 * @instant: if true turns on the windmill instantly i.e. without startup time
 *           e.g. used to get energy directly at time 0;
*/
void Windmill::activate(bool instant) { //:TODO: was aktivieren?
  //TODO: if running write to log!
  if(!running) {
    startTime = Simulation::getTime();
    if(instant) startTime -= startupTime;
  }
  running = true;
}

void Windmill::deactivate() { //TODO: was deaktivieren?
  //TODO: if !running write to log!
  //TODO: was wenn deaktiviert, wenn grade aktiviert wird?
  running = false;
}

void Windmill::dump(std::ostringstream& out) {
  out << "      Producer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

int Windmill::getCurrentEnergy() throw (exception::EnergyException) {
  // no energy plan, not running or within startup time -> no energy
  if(energyPlans.empty()) return 0.0;
  if(!running) return 0.0;
  if(running && Simulation::getTime() - startupTime < startTime) return 0.0;

  // up and running -> energy
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
