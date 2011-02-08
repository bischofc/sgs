#ifndef simulation_endpoint_consumer_washer_h
#define simulation_endpoint_consumer_washer_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Washer : public Consumer {

 public:
  Washer(std::string consumerId) : Consumer(consumerId) {
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Sat;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    int start = config::EnergyPlan::convertTime(14);
    int duration = config::EnergyPlan::convertTime(3);
    int startVariation = config::EnergyPlan::convertTime(0,30);
    int durationVariation = config::EnergyPlan::convertTime(0,15);
    double energy = config::EnergyPlan::getEnergyFromWattage(450);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~Washer() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_washer_h
