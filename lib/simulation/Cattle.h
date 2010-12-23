#ifndef simulation_endpoint_consumer_cattle_h
#define simulation_endpoint_consumer_cattle_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Cattle : public Consumer {

 public:
  Cattle(std::string consumerId) : Consumer(consumerId) {
    addEnergyPlan(new config::EnergyPlanStatic(390, 393, -1, -1, 0, 33));
    addEnergyPlan(new config::EnergyPlanStatic(1110, 1113, -1, -1, 0, 33));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_cattle_h
