#ifndef simulation_endpoint_consumer_microwave_h
#define simulation_endpoint_consumer_microwave_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Microwave : public Consumer {

 public:
  Microwave(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(1000);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(12,0);
    startVariation = config::EnergyPlan::convertTime(1);
    duration = config::EnergyPlan::convertTime(0,3);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, startVariation)));
  }

  virtual ~Microwave() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_microwave_h
