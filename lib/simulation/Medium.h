#ifndef simulation_medium_Medium_h
#define simulation_medium_Medium_h

#include <vector>
#include <sstream>

#include "MediumEndpoint.h"
#include "EnergyException.h"


namespace simulation {
namespace medium {

class Medium {
  std::string name;
  std::vector< endpoint::MediumEndpoint * > endpointList;
  int energy;

 public:
  Medium(std::string);
  void registerEndpoint(endpoint::MediumEndpoint *);
  void dump(std::ostringstream&);
  int oneStep() throw (exception::EnergyException);
  int getCurrentEnergy();

  // virtual destructor for interface 
  virtual ~Medium() { }
};

} /* End of namespace simulation::medium */
} /* End of namespace simulation */

#endif // simulation_medium_Medium_h
