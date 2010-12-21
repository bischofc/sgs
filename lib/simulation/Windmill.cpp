#include "Windmill.h"

namespace simulation {
namespace endpoint {
namespace producer {


Windmill::Windmill(std::string producerId) : Producer(producerId) {
  // build windmill behavior

  // set startup time
  startupTime = 3;

  // set energy parameters and add to energy plan
  std::map<std::string, std::string> params;
  std::pair<std::string, std::string> start ("start", "-1");
  params.insert(start);
  std::pair<std::string, std::string> end ("end", "-1");
  params.insert(end);
  std::pair<std::string, std::string> rate ("rate", "100");
  params.insert(rate);
  config::EnergyDistributionPlan * plan = config::EnergyDistributionPlanFactory::getInstance("static", params);
  addEnergyPlan(plan);

  // start windmill directly
  activate(true);
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
