#ifndef simulation_endpoint_producer_producerOwner_h
#define simulation_endpoint_producer_producerOwner_h

#include "Producer.h"
#include "MediumEndpoint.h"

namespace simulation {
namespace endpoint {
namespace producer {

class ProducerOwner : public simulation::endpoint::MediumEndpoint {
  std::string id;
  int nextPossibleStart;
  double purchasedEnergy;
  double tooMuchEnergyCounter;
  std::vector< Producer * > producerList;

private:
  void addNewProducer();
  void removeProducer();

public:
  ProducerOwner(std::string ownerId);
  std::string getId();
  void dump(std::ostringstream &out);
  void addProducer(Producer *);
  double getEnergy() throw (exception::EnergyException);
  void postStepAction(int energy);
  double notEnoughEnergyAction(double);

};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producerOwner_h
