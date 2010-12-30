#ifndef simulation_endpoint_consumer_consumerOwner_h
#define simulation_endpoint_consumer_consumerOwner_h

#include "MediumEndpoint.h"
#include "Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ConsumerOwner : public simulation::endpoint::MediumEndpoint {
  std::string id;
  std::vector< Consumer * > consumerList;

 public:
  ConsumerOwner(std::string ownerId);
  std::string getId();
  void dump(std::ostringstream&);
  void addConsumer(Consumer *);
  double getEnergy() throw (exception::EnergyException);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumerOwner_h
