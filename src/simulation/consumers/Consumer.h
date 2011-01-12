#ifndef simulation_endpoint_consumer_consumer_h
#define simulation_endpoint_consumer_consumer_h

#include <sstream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Parsable.h"
#include "energy/EnergyPlan.h"
#include "exceptions/EnergyException.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Consumer : public Parsable {
protected:
  std::string id;
  std::vector< boost::shared_ptr<config::EnergyPlan> > energyPlans;

public:
  void dump(std::ostringstream&);
  double getCurrentEnergy() throw (exception::EnergyException);
  virtual ~Consumer() { }

protected:
  Consumer(std::string);
  void addEnergyPlan(boost::shared_ptr<config::EnergyPlan>);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumer_h
