#ifndef simulation_endpoint_consumer_heater_h
#define simulation_endpoint_consumer_heater_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Heater : public Consumer {

 public:
  Heater(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double hEnergy = config::EnergyPlan::getEnergyFromWattage(300);
    double lEnergy = config::EnergyPlan::getEnergyFromWattage(50);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int intervall = config::EnergyPlan::convertTime(1);
    int hightime = config::EnergyPlan::convertTime(0,20);
    int variation = config::EnergyPlan::convertTime(1);

    start = config::EnergyPlan::convertTime(7,0);
    end = config::EnergyPlan::convertTime(22);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, intervall, hightime, lEnergy, hEnergy, variation, variation)));
  }

  virtual ~Heater() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_heater_h
