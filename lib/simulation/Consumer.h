#ifndef simulation_endpoint_consumer_consumer_h
#define simulation_endpoint_consumer_consumer_h

#include <EnergyDistributionPlan.h>
#include <sstream>
#include <vector>

namespace simulation {
namespace endpoint {
namespace consumer {

class Consumer {
protected:
  std::string id;
  std::vector<config::EnergyDistributionPlan *> energyPlans;

public:
  virtual void dump(std::ostringstream&) =0;
  virtual int getCurrentEnergy() =0;
  virtual void addEnergyPlan(config::EnergyDistributionPlan *) =0;
  // virtual destructor for interface 
  virtual ~Consumer() { }
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumer_h
