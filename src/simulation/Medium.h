#ifndef simulation_medium_medium_h
#define simulation_medium_medium_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include "exceptions/EnergyException.h"
#include "consumers/ConsumerOwner.h"
#include "producers/ProducerOwner.h"


namespace simulation {
namespace medium {

class Medium : public Parsable {
  std::string name;
  std::vector<int> loadAdjustment;
  std::vector< boost::shared_ptr<endpoint::consumer::ConsumerOwner> > consumerOwnerList;
  boost::shared_ptr<endpoint::producer::ProducerOwner> producerOwner;
  double energy;
  bool producerOwnerSet;

 public:
  Medium(std::string);
  void registerConsumerOwner(boost::shared_ptr<endpoint::consumer::ConsumerOwner>);
  void registerProducerOwner(boost::shared_ptr<endpoint::producer::ProducerOwner>);
  void dump(std::ostringstream&);
  void oneStep() throw (exception::EnergyException);
  int getNumberOfConsumers();                                                   //TODO weg?
  double getCurrentEnergy();
  virtual ~Medium() {}
};

} /* End of namespace simulation::medium */
} /* End of namespace simulation */

#endif // simulation_medium_medium_h
