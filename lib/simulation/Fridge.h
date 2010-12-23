#ifndef simulation_endpoint_consumer_fridge_h
#define simulation_endpoint_consumer_fridge_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {
//  void addEnergyPlan(config::EnergyPlan *);

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    addEnergyPlan(new config::EnergyPlanStatic(-1, -1, 60, 10, 0, 3));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_fridge_h
