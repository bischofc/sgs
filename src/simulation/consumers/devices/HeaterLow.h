#ifndef simulation_endpoint_consumer_heater_low_h
#define simulation_endpoint_consumer_heater_low_h

#include "energy/plans/EnergyPlanSelectivePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class HeaterLow : public Consumer {

 public:
  HeaterLow(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double hEnergy = config::EnergyPlan::getEnergyFromWattage(300);
    double lEnergy = config::EnergyPlan::getEnergyFromWattage(50);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int intervall = config::EnergyPlan::convertTime(1);
    int hightime = config::EnergyPlan::convertTime(0,20);
    int variation = config::EnergyPlan::convertTime(1,30);

    start = config::EnergyPlan::convertTime(6);
    end = config::EnergyPlan::convertTime(8);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod(day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, variation, variation)));

    start = config::EnergyPlan::convertTime(16);
    end = config::EnergyPlan::convertTime(22,45);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelectivePeriod(day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, variation, variation)));
  }

  virtual ~HeaterLow() {}
};

}}} /* End of namespaces */

#endif
