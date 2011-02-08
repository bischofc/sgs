
#ifndef simulation_config_energyPlanStatic_h
#define simulation_config_energyPlanStatic_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanStatic : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  double currentEnergy;

public:
  EnergyPlanStatic(double energy);
  double getCurrentEnergy();
  virtual ~EnergyPlanStatic() { }
};

}} /* End of namespaces */

#endif
