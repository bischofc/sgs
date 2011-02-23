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

    start = config::EnergyPlan::convertTime(5,30);
    end = config::EnergyPlan::convertTime(8,30);
    startVariation = config::EnergyPlan::convertTime(0,30);
    endVariation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(18);
    end = config::EnergyPlan::convertTime(22,30);
    startVariation = config::EnergyPlan::convertTime(1);
    endVariation = config::EnergyPlan::convertTime(1);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, 0, endVariation)));

    // in 30% of all households
    if(helper::RandomNumbers::getRandom() < 0.5) {
      start = config::EnergyPlan::convertTime(2,30);
      end = config::EnergyPlan::convertTime(4,30);
      startVariation = config::EnergyPlan::convertTime(2);
      endVariation = config::EnergyPlan::convertTime(2);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));
    }
  }

  virtual ~LightLow() {}
};

}}} /* End of namespaces */

#endif
