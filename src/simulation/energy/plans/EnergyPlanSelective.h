
#ifndef simulation_config_energyPlanSelective_h
#define simulation_config_energyPlanSelective_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanSelective : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  int nextEventTime, start, time, maxStartVariation, maxTimeVariation;
  int startVariation, timeVariation;
  double currentEnergy, highEnergy;
  Runtimes runtimes;
  TimeType ttype;

private:
  void updateState();

public:
  EnergyPlanSelective(Runtimes runtimes, TimeType ttype, int start, int time, double energy,
                  int maxStartVariation=0, int maxTimeVariation=0);
  double getCurrentEnergy();
  virtual ~EnergyPlanSelective() { }
};

}} /* End of namespaces */

#endif
