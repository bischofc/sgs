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
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(6,30);
    end = config::EnergyPlan::convertTime(7,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, 15, 15)));

    start = config::EnergyPlan::convertTime(17,30);
    end = config::EnergyPlan::convertTime(22,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, 0, 30)));
  }

  virtual ~Light() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_light_h
