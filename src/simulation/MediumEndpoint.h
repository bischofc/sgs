
#ifndef simulation_endpoint_mediumEndpoint_h
#define simulation_endpoint_mediumEndpoint_h

#include <sstream>
#include <boost/shared_ptr.hpp>

#include "Parsable.h"

namespace simulation {
namespace endpoint {

class MediumEndpoint : public Parsable {

 public:
  virtual std::string getId()  = 0;
  virtual void dump(std::ostringstream&) =0;
  virtual double getEnergy() =0;

public:
  virtual ~MediumEndpoint() { }

};

} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_mediumEndpoint_h
