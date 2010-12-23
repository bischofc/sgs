#ifndef simulation_endpoint_consumer_Cattle_h
#define simulation_endpoint_consumer_Cattle_h

#include "Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Cattle : public Consumer {

 public:
  Cattle(std::string consumerId) : Consumer(consumerId) {
    addEnergyPlan(getBasicEnergyPlan(390, 393, -1, -1, 0, 33));
    addEnergyPlan(getBasicEnergyPlan(1110, 1113, -1, -1, 0, 33));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_Cattle_h
