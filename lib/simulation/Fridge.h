#ifndef simulation_endpoint_consumer_Fridge_h
#define simulation_endpoint_consumer_Fridge_h

#include "Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    addEnergyPlan(getBasicEnergyPlan(-1, -1, 60, 10, 0, 3));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_Fridge_h
