#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(30);

    start = config::EnergyPlan::convertTime(7);
    end = config::EnergyPlan::convertTime(7,30);
    addEnergyPlan(new config::EnergyPlanStatic(start, end, energy));

    start = config::EnergyPlan::convertTime(11);
    end = config::EnergyPlan::convertTime(12);
    addEnergyPlan(new config::EnergyPlanStatic(start, end, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
