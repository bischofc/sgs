#ifndef simulation_endpoint_consumer_light_h
#define simulation_endpoint_consumer_light_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Light : public Consumer {

public:
  Light(std::string consumerId) : Consumer(consumerId) {
    int start, end, startVariation, endVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(6,30);
    end = config::EnergyPlan::convertTime(7,30);
    startVariation = config::EnergyPlan::convertTime(0,15);
    endVariation = config::EnergyPlan::convertTime(0,15);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(17,30);
    end = config::EnergyPlan::convertTime(22,30);
    endVariation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, 0, endVariation)));
  }

  virtual ~Light() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_light_h
