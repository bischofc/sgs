#ifndef simulation_endpoint_consumer_heater_h
#define simulation_endpoint_consumer_heater_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Heater : public Consumer {

 public:
  Heater(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(300);

    start = config::EnergyPlan::convertTime(7,0,15);
    end = config::EnergyPlan::convertTime(8,0,15);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));

    start = config::EnergyPlan::convertTime(17,0,15);
    end = config::EnergyPlan::convertTime(22,0,15);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }

  virtual ~Heater() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_heater_h
