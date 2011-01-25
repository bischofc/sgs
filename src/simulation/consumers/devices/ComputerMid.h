#ifndef simulation_endpoint_consumer_computerMid_h
#define simulation_endpoint_consumer_computerMid_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerMid : public Consumer {

 public:
  ComputerMid(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);
    int duration = config::EnergyPlan::convertTime(1,30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(18);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 30, 30)));
  }

  virtual ~ComputerMid() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerMid_h
