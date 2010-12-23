#ifndef simulation_endpoint_producer_windmill_h
#define simulation_endpoint_producer_windmill_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace producer {

class Windmill : public Producer {

public:
  Windmill(std::string producerId) : Producer(producerId) {
    // set startup time
    startupTime = 3;

    // set energy plan(s)
    addEnergyPlan(new config::EnergyPlanStatic(-1, -1, -1, -1, 0, 150));

    // start windmill directly
    activate(true);
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_producer_Windmill_h
