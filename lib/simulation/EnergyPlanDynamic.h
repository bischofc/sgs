
#ifndef simulation_config_EnergyPlanDynamic_h
#define simulation_config_EnergyPlanDynamic_h

#include "Simulation.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

class EnergyPlanDynamic : public EnergyPlan {
  int period, highTime, lowEnergy, highEnergy;
  vector<float> highEnergyValues;

public:
  EnergyPlanDynamic(int, int, int, int, int, int);
  float getCurrentEnergy();
};

}}

#endif /* simulation_config_EnergyPlanDynamic_h */
