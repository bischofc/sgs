#ifndef simulation_endpoint_producer_producerOwner_h
#define simulation_endpoint_producer_producerOwner_h

#include "Producer.h"

namespace simulation {
namespace endpoint {
namespace producer {

class ProducerOwner {
  int nextPossibleStart;
  double purchasedEnergy;
  double tooMuchEnergyCounter;
  std::vector< boost::shared_ptr<Producer> > producerList;
  std::string id;

private:
  void addNewProducer();
  void removeProducer();

public:
  ProducerOwner(std::string ownerId);
  virtual ~ProducerOwner() {}
  std::string getId();
  void dump(std::ostringstream &out);
  void addProducer(boost::shared_ptr<Producer>);
  double getEnergy() throw (exception::EnergyException);
  void postStepAction(double energy);                                           //TODO benötigt?
  double notEnoughEnergyAction(double);
  std::vector<int> getLoadAdjustment();

};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producerOwner_h
