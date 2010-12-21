#ifndef simulation_endpoint_consumer_Fridge_h
#define simulation_endpoint_consumer_Fridge_h

#include "Consumer.h"
#include "EnergyDistributionPlanFactory.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {

 public:
  Fridge(std::string consumerId);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_Fridge_h
