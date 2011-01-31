#ifndef simulation_endpoint_consumer_oven_h
#define simulation_endpoint_consumer_oven_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Oven : public Consumer {

 public:
  Oven(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Weekend;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(12);
    startVariation = config::EnergyPlan::convertTime(0,15);
    duration = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, startVariation)));
  }

  virtual ~Oven() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_oven_h
