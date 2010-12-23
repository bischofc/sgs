
#ifndef simulation_config_energyPlanDynamic_h
#define simulation_config_energyPlanDynamic_h

#include "EnergyPlan.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

class EnergyPlanDynamic : public EnergyPlan {
  int start, end, period, highTime, lowEnergy, highEnergy;
  vector<float> highEnergyValues;

public:
  EnergyPlanDynamic(int, int, int, int, int, int);
  float getCurrentEnergy();
};

}}

#endif /* simulation_config_energyPlanDynamic_h */
