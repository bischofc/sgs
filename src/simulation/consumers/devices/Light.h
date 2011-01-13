#ifndef simulation_endpoint_consumer_light_h
#define simulation_endpoint_consumer_light_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Light : public Consumer {

public:
  Light(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);

    start = config::EnergyPlan::convertTime(6,30);
    end = config::EnergyPlan::convertTime(7,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));

    start = config::EnergyPlan::convertTime(17);
    end = config::EnergyPlan::convertTime(22,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }

  virtual ~Light() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_light_h
