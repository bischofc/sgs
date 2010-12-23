#include "EnergyPlanStatic.h"
#include "Simulation.h"

namespace simulation {
namespace config {

EnergyPlanStatic::EnergyPlanStatic(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
  init(start, end, period, highTime, lowEnergy, highEnergy);
}

EnergyPlanStatic::EnergyPlanStatic(int start, int end, int energy) {
  init(start, end, -1, -1, 0, energy);
}

void EnergyPlanStatic::init(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
  this->start = start;
  this->end = end;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
}

float EnergyPlanStatic::getCurrentEnergy() {
  if((this->start >= 0 && Simulation::getTime() < this->start) ||
                  (this->end >= 0 && Simulation::getTime() > this->end)) {
    return 0;
  }

  if(period < 0) {
    if(highTime < 0) return highEnergy;
    else {
      if(Simulation::getTime() < highTime) return highEnergy;
      else return lowEnergy;
    }
  } else {
    if(highTime < 1) throw exception::EnergyException("Undefined behavior: negative or zero 'highTime' within 'period' (you might want to use 'period=-1')");
    int currTime = Simulation::getTime() % period;
    if(currTime < highTime) return highEnergy;
    else return lowEnergy;
  }

  throw exception::EnergyException("Parameters of energy plan are unexpected: Possibly bug! (EnergyPlanStatic)");
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
