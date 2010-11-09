#ifndef simulation_endpoint_producer_producer_h
#define simulation_endpoint_producer_producer_h

#include <EnergyDistributionPlan.h>
#include <EnergyException.h>
#include <sstream>
#include <vector>

namespace simulation {
namespace endpoint {
namespace producer {

class Producer {
protected:
  std::string id;
  std::vector<config::EnergyDistributionPlan *> energyPlans;

public:
  virtual void dump(std::ostringstream&) =0;
  virtual int getCurrentEnergy() throw (exception::EnergyException) =0;
  virtual void addEnergyPlan(config::EnergyDistributionPlan *) =0;
  // virtual destructor for interface 
  virtual ~Producer() { }
};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producer_h
