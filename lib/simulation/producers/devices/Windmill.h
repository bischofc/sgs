#ifndef simulation_endpoint_producer_windmill_h
#define simulation_endpoint_producer_windmill_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace producer {

class Windmill : public Producer {

public:
  Windmill(std::string producerId, bool startInstantly) : Producer(producerId) {
    // set startup time
    startupTime = config::EnergyPlan::convertTime(0,10);

    // set energy plan(s)
    addEnergyPlan(new config::EnergyPlanStatic(-1, -1, 50));

    // start windmill directly
    activate(startInstantly);
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_producer_Windmill_h
