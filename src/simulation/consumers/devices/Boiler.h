#ifndef simulation_endpoint_consumer_boiler_h
#define simulation_endpoint_consumer_boiler_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Boiler : public Consumer {

 public:
  Boiler(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int duration = config::EnergyPlan::convertTime(0,15);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(7);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 0, 10)));

    start = config::EnergyPlan::convertTime(19,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 0, 10)));
  }

  virtual ~Boiler() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_boiler_h
