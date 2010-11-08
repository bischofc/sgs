#ifndef simulation_medium_Medium_h
#define simulation_medium_Medium_h

#include <MediumEndpoint.h>
#include <EnergyException.h>
#include <vector>
#include <sstream>
#include <iostream>


namespace simulation {
namespace medium {

class Medium {

 public:

  Medium(std::string);
  void registerEndpoint(endpoint::MediumEndpoint *);
  int oneStep() throw (exception::EnergyException);
  void dump(std::ostringstream&);

public:
  // virtual destructor for interface 
  virtual ~Medium() { } // todo *delete* alle elemente in endpointList

private:
  std::string name;
  std::vector< endpoint::MediumEndpoint * > endpointList;

};

} /* End of namespace simulation::medium */
} /* End of namespace simulation */

#endif // simulation_medium_Medium_h
