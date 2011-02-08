#ifndef simulation_endpoint_consumer_light_high_h
#define simulation_endpoint_consumer_light_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class LightHigh : public Consumer {

public:
  LightHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end, startVariation, endVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(5,30);
    end = config::EnergyPlan::convertTime(8);
    startVariation = config::EnergyPlan::convertTime(2);
    endVariation = config::EnergyPlan::convertTime(2);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(17,30);
    end = config::EnergyPlan::convertTime(24,0);
    startVariation = config::EnergyPlan::convertTime(1);
    endVariation = config::EnergyPlan::convertTime(0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, 0, endVariation)));

    start = config::EnergyPlan::convertTime(0);
    end = config::EnergyPlan::convertTime(1,0);
    startVariation = config::EnergyPlan::convertTime(0);
    endVariation = config::EnergyPlan::convertTime(2);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, 0, endVariation)));
  }

  virtual ~LightHigh() {}
};

}}} /* End of namespaces */

#endif
