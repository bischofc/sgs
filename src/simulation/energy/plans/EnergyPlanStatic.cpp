#include "EnergyPlanStatic.h"
#include "Simulation.h"

namespace simulation {
namespace config {

//TODO bei Konstruktoren sanity checks

EnergyPlanStatic::EnergyPlanStatic(double energy) {                             //TODO Energie variieren?
  init(Permanent, Off, -1, -1, -1, -1, 0, energy, 0, 0, 0);
}

EnergyPlanStatic::EnergyPlanStatic(int period, int highTime, double lowEnergy, double highEnergy, int maxHighTimeVariation) {
  init(Permanent, Off, -1, -1, period, highTime, lowEnergy, highEnergy, 0, 0, maxHighTimeVariation);
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, double energy, int maxStartVariation, int maxTimeVariation) {
  init(runtimes, ttype, start, time, -1, -1, 0, energy, maxStartVariation, maxTimeVariation, 0);
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int maxStartVariation, int maxTimeVariation, int maxHighTimeVariation) {
  init(runtimes, ttype, start, time, period, highTime, lowEnergy, highEnergy, maxStartVariation, maxTimeVariation, maxHighTimeVariation);
}

void EnergyPlanStatic::init(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int msv, int mtv, int mhtv) {
  this->nextEventTime = 0;
  this->currentEnergy = 0;
  this->running = false;

  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->maxStartVariation = msv;
  this->maxTimeVariation = mtv;
  this->maxHighTimeVariation = mhtv;
}

double EnergyPlanStatic::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanStatic::updateState() {
  int simulationTime = Simulation::getTime();

  //// permanent
  if(runtimes == Permanent) {

    // non-periodical
    if(period <= 0) {
      currentEnergy = highEnergy;
      nextEventTime = -1;
    }

    // periodical
    else {
      int periodTime = simulationTime % period;
      if(periodTime < highTime) {
        currentEnergy = highEnergy;
        nextEventTime = simulationTime + highTime;
      } else {
        nextEventTime = simulationTime + period;
        currentEnergy = lowEnergy;
      }
    }
  }

  //// non-permanent
  else {

    // non-periodical and periodical
    if(getDayOfTheWeek() & runtimes) {
      int currTime = getTimeOfDay();
      int end = (ttype == EnergyPlan::Duration) ? start + time : time;
      if(currTime < start || currTime > end) {
        currentEnergy = 0;
        //TODO ab hier weiter: welcher tag? nächster, zwei weiter.. ?
      } else {

        // non-periodical
        if(period <= 0) {
          currentEnergy = highEnergy;
        }

        // periodical
        else {
          int periodTime = currTime % period;
          if(periodTime < highTime) {
            currentEnergy = highEnergy;
          } else {
            currentEnergy = lowEnergy;
          }
        }
      }
    }
  }
}

//{
//  if((this->start >= 0 && Simulation::getTime() < this->start) ||
//                  (this->end >= 0 && Simulation::getTime() > this->end)) {
//    return 0.0;
//  }
//
//  if(period < 0) {
//    if(highTime < 0) return highEnergy;
//    else {
//      if(Simulation::getTime() < highTime) return highEnergy;
//      else return lowEnergy;
//    }
//  } else {
//    if(highTime < 1) throw exception::EnergyException("Undefined behavior: negative or zero 'highTime' within 'period' (you might want to use 'period=-1')");
//    int currTime = Simulation::getTime() % period;
//    if(currTime < highTime) return highEnergy;
//    else return lowEnergy;
//  }
//
//  throw exception::EnergyException("Parameters of energy plan are unexpected: Possibly bug! (EnergyPlanStatic)");
//}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
