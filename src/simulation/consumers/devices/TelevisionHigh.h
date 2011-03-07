#ifndef simulation_endpoint_consumer_television_high_h
#define simulation_endpoint_consumer_television_high_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class TelevisionHigh : public Consumer {

 public:
  TelevisionHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end, startVariation, endVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(helper::RandomNumbers::getRandom(90,200));
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    config::EnergyPlan::Runtimes day;

    start = config::EnergyPlan::convertTime(19);
    startVariation = config::EnergyPlan::convertTime(2);
    end = config::EnergyPlan::convertTime(22,30);
    endVariation = config::EnergyPlan::convertTime(2);
    day = config::EnergyPlan::Alldays;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    start = config::EnergyPlan::convertTime(15);
    startVariation = config::EnergyPlan::convertTime(4);
    end = config::EnergyPlan::convertTime(18);
    endVariation = config::EnergyPlan::convertTime(2);
    day = config::EnergyPlan::Alldays;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));

    // in 7% of the households
    if(helper::RandomNumbers::getRandom() < 0.07) {
      start = config::EnergyPlan::convertTime(2);
      startVariation = config::EnergyPlan::convertTime(1);
      end = config::EnergyPlan::convertTime(5);
      endVariation = config::EnergyPlan::convertTime(1);
      day = config::EnergyPlan::Alldays;
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, startVariation, endVariation)));
    }
  }

  virtual ~TelevisionHigh() {}
};

}}} /* End of namespaces */

#endif