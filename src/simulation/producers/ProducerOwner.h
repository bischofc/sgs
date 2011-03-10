#ifndef simulation_endpoint_producer_producerOwner_h
#define simulation_endpoint_producer_producerOwner_h

#include "Producer.h"

namespace simulation {
namespace endpoint {
namespace producer {

class ProducerOwner {
  std::string id;
  std::vector< boost::shared_ptr<Producer> > producerList;
  double referenceLoadCurves[7][24];

private:
  std::vector<double> getForecastLoadCurve();

public:
  ProducerOwner(std::string ownerId);
  virtual ~ProducerOwner() {}
  std::string getId();
  void dump(std::ostringstream &out);
  void addProducer(boost::shared_ptr<Producer>);
  std::vector<double> getLoadAdjustment(int households);
};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_producerOwner_h
