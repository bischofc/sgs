#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(60); //TODO 3/60 = 0 anpassen zu float und schauen ob die genauigkeit ok ist (auch bei 3/3600)

    addEnergyPlan(new config::EnergyPlanStatic(420, 450, energy));
    addEnergyPlan(new config::EnergyPlanStatic(660, 720, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
