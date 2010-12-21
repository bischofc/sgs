#ifndef simulation_endpoint_producer_producer_h
#define simulation_endpoint_producer_producer_h

#include <EnergyDistributionPlan.h>
#include <EnergyException.h>
#include <sstream>
#include <vector>
#include <map>

namespace simulation {
namespace endpoint {
namespace producer {

class Producer {
protected:
  std::string id;
  std::vector<config::EnergyDistributionPlan *> energyPlans;
  bool running;
  int startupTime;
  int startTime;

public:
  virtual void activate(bool) =0;
  virtual void deactivate() =0;
  virtual void dump(std::ostringstream&) =0;
  virtual int getCurrentEnergy() throw (exception::EnergyException) =0;
  virtual ~Producer() { }

private:
  virtual void addEnergyPlan(config::EnergyDistributionPlan *) =0;
};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producer_h
