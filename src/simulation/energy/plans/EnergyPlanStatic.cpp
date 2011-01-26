#include "EnergyPlanStatic.h"
#include "Simulation.h"

namespace simulation {
namespace config {

//TODO bei Konstruktoren sanity checks

EnergyPlanStatic::EnergyPlanStatic(double energy) {                             //TODO Energie variieren?
  this->nextEventTime = 0;
  init(Permanent, Off, -1, -1, -1, -1, 0, energy, 0, 0, 0);
}

EnergyPlanStatic::EnergyPlanStatic(int period, int highTime, double lowEnergy, double highEnergy, int maxHighTimeVariation) {
  this->nextEventTime = 0;
  init(Permanent, Off, -1, -1, period, highTime, lowEnergy, highEnergy, 0, 0, maxHighTimeVariation);
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, double energy, int maxStartVariation, int maxTimeVariation) {
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start;
  init(runtimes, ttype, start, time, -1, -1, 0, energy, maxStartVariation, maxTimeVariation, 0);
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int maxStartVariation, int maxTimeVariation, int maxHighTimeVariation) {
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start;
  init(runtimes, ttype, start, time, period, highTime, lowEnergy, highEnergy, maxStartVariation, maxTimeVariation, maxHighTimeVariation);
}

void EnergyPlanStatic::init(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int msv, int mtv, int mhtv) {
  this->currentEnergy = 0;
  this->running = false;                                                        //TODO vllt weg

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
        currentEnergy = lowEnergy;
        nextEventTime = simulationTime + (period - highTime);
      }
    }
  }

  //// non-permanent
  else {

    // non-periodical and periodical
    if(getDayOfTheWeek() & runtimes) {
      int currTime = getTimeOnCurrentDay();
      int localEnd = (ttype == EnergyPlan::Duration) ? start + time : time;
      int nextEnd = (simulationTime - currTime) + localEnd;

      // at end
      if(currTime >= localEnd) {
        currentEnergy = 0;
        nextEventTime = getAbsTimeOfNextRuntimeDay(runtimes) + start;

      // before start
      } else if(currTime < start) {
        currentEnergy = 0;
        nextEventTime = (simulationTime - currTime) + start;

      // at start or beginning of period
      } else {

        // non-periodical
        // start to right before end
        if(period <= 0) {
          currentEnergy = highEnergy;
          nextEventTime = nextEnd;
        }

        // periodical
        else {
          int periodTime = (currTime - start) % period;
          int tmp;

          // at start or beginning of period
          if(periodTime < highTime) {
            currentEnergy = highEnergy;
            tmp = (simulationTime - periodTime) + highTime;

          // in period after highTime
          } else {
            currentEnergy = lowEnergy;
            tmp = (simulationTime - periodTime) + period;
          }
          nextEventTime = (nextEnd < tmp) ? nextEnd : tmp;
        }
      }
    }
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
