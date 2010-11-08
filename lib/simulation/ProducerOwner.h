#ifndef simulation_endpoint_producer_producerOwner_h
#define simulation_endpoint_producer_producerOwner_h

#include <vector>
#include <MediumEndpoint.h>
#include <Producer.h>

namespace simulation {
namespace endpoint {
namespace producer {

class ProducerOwner : public simulation::endpoint::MediumEndpoint {
  std::string id;

 public:
  ProducerOwner(std::string ownerId);
  std::string getId();
  void dump(std::ostringstream &out);
  void addProducer(Producer *);
  int getEnergy();

 private:

  /**
   * @element-type Windmill
   */
  std::vector< Producer * > producerList;
};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producerOwner_h
