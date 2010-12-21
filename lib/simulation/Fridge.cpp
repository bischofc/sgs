#include "Fridge.h"

namespace simulation {
namespace endpoint {
namespace consumer {


Fridge::Fridge(std::string consumerId) : Consumer(consumerId) {
  // build fridge behavior

  // set energy parameters and add to energy plan
  std::map<std::string, std::string> params;
  std::pair<std::string, std::string> start ("start", "-1");
  params.insert(start);
  std::pair<std::string, std::string> end ("end", "-1");
  params.insert(end);
  std::pair<std::string, std::string> p ("period", "10");
  params.insert(p);
  std::pair<std::string, std::string> ht ("highTime", "5");
  params.insert(ht);
  std::pair<std::string, std::string> le ("lowEnergy", "1");
  params.insert(le);
  std::pair<std::string, std::string> he ("highEnergy", "10");
  params.insert(he);
  config::EnergyDistributionPlan * plan = config::EnergyDistributionPlanFactory::getInstance("repeat", params);
  addEnergyPlan(plan);
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
