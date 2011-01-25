#ifndef simulation_endpoint_consumer_kettle_h
#define simulation_endpoint_consumer_kettle_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Kettle : public Consumer {

 public:
  Kettle(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int duration = config::EnergyPlan::convertTime(0,3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(7,0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 30)));

    start = config::EnergyPlan::convertTime(18,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 60)));
  }

  virtual ~Kettle() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_kettle_h
