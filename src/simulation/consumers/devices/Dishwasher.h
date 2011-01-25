#ifndef simulation_endpoint_consumer_dishwasher_h
#define simulation_endpoint_consumer_dishwasher_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Dishwasher : public Consumer {

 public:
  Dishwasher(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(300);
    int duration = config::EnergyPlan::convertTime(3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(19,00);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 30)));
  }

  virtual ~Dishwasher() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_dishwasher_h
