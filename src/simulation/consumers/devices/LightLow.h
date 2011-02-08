#ifndef simulation_endpoint_consumer_light_low_h
#define simulation_endpoint_consumer_light_low_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class LightLow : public Consumer {

public:
  LightLow(std::string consumerId) : Consumer(consumerId) {
    int start, end, startVariation, endVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(6,30);
    end = config::EnergyPlan::convertTime(7,30);
    startVariation = config::EnergyPlan::convertTime(0,30);
    endVariation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(18);
    end = config::EnergyPlan::convertTime(22,30);
    startVariation = config::EnergyPlan::convertTime(1);
    endVariation = config::EnergyPlan::convertTime(1);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, 0, endVariation)));
  }

  virtual ~LightLow() {}
};

}}} /* End of namespaces */

#endif
