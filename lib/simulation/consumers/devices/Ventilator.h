#ifndef simulation_endpoint_consumer_ventilator_h
#define simulation_endpoint_consumer_ventilator_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Ventilator : public Consumer {

 public:
  Ventilator(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(45);

    addEnergyPlan(new config::EnergyPlanStatic(1000, 1350, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_ventilator_h
