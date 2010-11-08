
#ifndef simulation_endpoint_MediumEndpoint_h
#define simulation_endpoint_MediumEndpoint_h

#include <sstream>

namespace simulation {
namespace endpoint {

class MediumEndpoint {

 public:
  virtual std::string getId()  = 0;
  virtual void dump(std::ostringstream&) =0;
  virtual int getEnergy() =0;

public:
  // virtual destructor for interface 
  virtual ~MediumEndpoint() { }

};

} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_MediumEndpoint_h
