#ifndef simulation_endpoint_consumer_consumer_h
#define simulation_endpoint_consumer_consumer_h

#include <sstream>
#include <vector>

#include "EnergyPlan.h"
#include "EnergyException.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Consumer {
protected:
  std::string id;
  std::vector<config::EnergyPlan *> energyPlans;

public:
  void dump(std::ostringstream&);
  double getCurrentEnergy() throw (exception::EnergyException);
  virtual ~Consumer() { }

protected:
  Consumer(std::string);
  void addEnergyPlan(config::EnergyPlan *);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumer_h
