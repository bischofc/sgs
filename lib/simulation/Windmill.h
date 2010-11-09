#ifndef simulation_endpoint_producer_Windmill_h
#define simulation_endpoint_producer_Windmill_h

#include <Producer.h>


namespace simulation {
namespace endpoint {
namespace producer {

class Windmill : public Producer {

public:
  Windmill(std::string producerId);
  void addEnergyPlan(config::EnergyDistributionPlan *);
  void dump(std::ostringstream&);
  int getCurrentEnergy() throw (exception::EnergyException);

};

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_producer_Windmill_h
