#ifndef simulation_medium_medium_h
#define simulation_medium_medium_h

#include <vector>
#include <boost/shared_ptr.hpp>

#include "MediumEndpoint.h"
#include "exceptions/EnergyException.h"


namespace simulation {
namespace medium {

class Medium : public Parsable {
  std::string name;
  std::vector< boost::shared_ptr<endpoint::MediumEndpoint> > endpointList;
  double energy;

 public:
  Medium(std::string);
  void registerEndpoint(boost::shared_ptr<endpoint::MediumEndpoint>);
  void dump(std::ostringstream&);
  void oneStep(double &, double &, double &) throw (exception::EnergyException);
  int getNumberOfConsumers();                                                   //TODO wird nur für debugging gebraucht (Size.h)
  double getCurrentEnergy();
  virtual ~Medium() {}
};

} /* End of namespace simulation::medium */
} /* End of namespace simulation */

#endif // simulation_medium_medium_h