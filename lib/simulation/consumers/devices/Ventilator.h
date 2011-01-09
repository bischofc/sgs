#ifndef simulation_endpoint_consumer_ventilator_h
#define simulation_endpoint_consumer_ventilator_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Ventilator : public Consumer {

 public:
  Ventilator(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(45);

    start = config::EnergyPlan::convertTime(16,30);
    end = config::EnergyPlan::convertTime(22,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_ventilator_h
