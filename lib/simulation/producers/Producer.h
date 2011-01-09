#ifndef simulation_endpoint_producer_producer_h
#define simulation_endpoint_producer_producer_h

#include <sstream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Parsable.h"
#include "energy/EnergyPlan.h"
#include "exceptions/EnergyException.h"

namespace simulation {
namespace endpoint {
namespace producer {

class Producer : public Parsable {
protected:
  std::string id;
  std::vector< boost::shared_ptr<config::EnergyPlan> > energyPlans;
  bool running;
  int startupTime;
  int startTime;

public:
  void dump(std::ostringstream&);
  int getStartupTime();
  double getCurrentEnergy() throw (exception::EnergyException);
  virtual ~Producer() {}

protected:
  Producer(std::string);
  void activate(bool instant = false);
  void deactivate();
  void addEnergyPlan( boost::shared_ptr<config::EnergyPlan> );
};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producer_h