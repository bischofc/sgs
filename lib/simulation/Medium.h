#ifndef simulation_medium_medium_h
#define simulation_medium_medium_h

#include <vector>

#include "MediumEndpoint.h"
#include "exceptions/EnergyException.h"


namespace simulation {
namespace medium {

class Medium {
  std::string name;
  std::vector< endpoint::MediumEndpoint * > endpointList;
  double energy;

 public:
  Medium(std::string);
  void registerEndpoint(endpoint::MediumEndpoint *);
  void dump(std::ostringstream&);
  int oneStep(double &, double &) throw (exception::EnergyException);
  double getCurrentEnergy();

  // virtual destructor for interface 
  virtual ~Medium() { }
};

} /* End of namespace simulation::medium */
} /* End of namespace simulation */

#endif // simulation_medium_medium_h
