#ifndef simulation_endpoint_consumer_boiler_low_h
#define simulation_endpoint_consumer_boiler_low_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class BoilerLow : public Consumer {

public:
  BoilerLow(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int period = config::EnergyPlan::convertTime(6);
    int duration = config::EnergyPlan::convertTime(0,20);
    int highTimeVariation = config::EnergyPlan::convertTime(0,10);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod(period, duration, 0, energy, highTimeVariation)));
  }

  virtual ~BoilerLow() {}
};

}}} /* End of namespaces */

#endif
