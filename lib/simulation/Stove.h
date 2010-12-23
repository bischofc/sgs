#ifndef simulation_endpoint_consumer_stove_h
#define simulation_endpoint_consumer_stove_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Stove : public Consumer {

 public:
  Stove(std::string consumerId) : Consumer(consumerId) {
    int energy = config::EnergyPlan::getEnergyFromWattage(3500);

    addEnergyPlan(new config::EnergyPlanStatic(660, 690, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_stove_h
