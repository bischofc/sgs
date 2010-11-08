#ifndef simulation_endpoint_consumer_consumerOwner_h
#define simulation_endpoint_consumer_consumerOwner_h

#include <vector>
#include <MediumEndpoint.h>
#include <Consumer.h>

namespace simulation {
namespace endpoint {
namespace consumer {

class ConsumerOwner : public simulation::endpoint::MediumEndpoint {
  std::string id;

 public:
  ConsumerOwner(std::string ownerId);
  std::string getId();
  void dump(std::ostringstream&);
  void addConsumer(Consumer *);
  int getEnergy();

 private:
  std::vector< Consumer * > consumerList;
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumerOwner_h
