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
    double energy = config::EnergyPlan::getEnergyFromWattage(300);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(7,0);
    end = config::EnergyPlan::convertTime(8,0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, 15, 15)));

    start = config::EnergyPlan::convertTime(17,0);
    end = config::EnergyPlan::convertTime(22,0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, 15, 15)));
  }

  virtual ~Heater() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_heater_h
