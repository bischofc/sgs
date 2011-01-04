#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(3); //TODO schauen ob die genauigkeit auch bei 3/3600 ok ist

    addEnergyPlan(new config::EnergyPlanStatic(420, 450, energy));
    addEnergyPlan(new config::EnergyPlanStatic(660, 720, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
