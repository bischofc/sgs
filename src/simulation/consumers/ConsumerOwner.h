#ifndef simulation_endpoint_consumer_consumerOwner_h
#define simulation_endpoint_consumer_consumerOwner_h

#include "consumers/Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ConsumerOwner {
  std::string id;
  std::vector< boost::shared_ptr<Consumer> > consumerList;

 public:
  ConsumerOwner(std::string ownerId);
  virtual ~ConsumerOwner() {}
  std::string getId();
  void dump(std::ostringstream&);
  void addConsumer(boost::shared_ptr<Consumer>);
  void adjustLoad(std::vector<double> adjustment);
  double getEnergy() throw (exception::EnergyException);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumerOwner_h
