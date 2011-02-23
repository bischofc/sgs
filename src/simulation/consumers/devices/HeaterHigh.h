#ifndef simulation_endpoint_consumer_heater_high_h
#define simulation_endpoint_consumer_heater_high_h

#include "energy/plans/EnergyPlanSelectivePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class HeaterHigh : public Consumer {

 public:
  HeaterHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double hEnergy = config::EnergyPlan::getEnergyFromWattage(300);
    double lEnergy = config::EnergyPlan::getEnergyFromWattage(50);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int intervall = config::EnergyPlan::convertTime(1);
    int hightime = config::EnergyPlan::convertTime(0,20);
    int startVariation = config::EnergyPlan::convertTime(1,30);
    int durationVariation = config::EnergyPlan::convertTime(0,20);

    start = config::EnergyPlan::convertTime(6,0);
    end = config::EnergyPlan::convertTime(22,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod(day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, startVariation, durationVariation)));

    // in 20% of all households
    if(helper::RandomNumbers::getRandom() < 0.2) {
      start = config::EnergyPlan::convertTime(2,30);
      end = config::EnergyPlan::convertTime(4,30);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod(day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, startVariation, durationVariation)));
    }
  }

  virtual ~HeaterHigh() {}
};

}}} /* End of namespaces */

#endif
