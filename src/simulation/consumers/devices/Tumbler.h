#ifndef simulation_endpoint_consumer_tumbler_h
#define simulation_endpoint_consumer_tumbler_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Tumbler : public Consumer {

 public:
  Tumbler(std::string consumerId) : Consumer(consumerId) {
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Sat;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    int start = config::EnergyPlan::convertTime(17);
    int duration = config::EnergyPlan::convertTime(2);
    int variation = config::EnergyPlan::convertTime(0,15);
    double energy = config::EnergyPlan::getEnergyFromWattage(900);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, variation, variation)));
  }

  virtual ~Tumbler() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_tumbler_h
