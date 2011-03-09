#include "ProducerOwner.h"
#include "DeviceFactory.h"
#include "Simulation.h"

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  this->id = ownerId;
  this->nextPossibleStart = 0;
  this->tooMuchEnergyCounter = 0;
}

std::string ProducerOwner::getId() {
  return 0;
}

double ProducerOwner::getEnergy() throw (exception::EnergyException) {
  double energy = 0.0;
  for(std::vector< boost::shared_ptr<Producer> >::iterator it = this->producerList.begin();
                  it != this->producerList.end(); it++) {
    energy += (*it)->getCurrentEnergy();
  }
  return energy;
}

// returns an empty vector if no adjustment is necessary
// otherwise a vector with 24 elements
std::vector<int> ProducerOwner::getLoadAdjustment() {
  //TODO hier weiter mit magic
  std::vector<int> tmp;
  return tmp;
}

void ProducerOwner::dump(std::ostringstream &out) {
  out << "    ProducerOwner-Id: " << this->id << std::endl;
  for(std::vector< boost::shared_ptr<Producer> >::iterator it = this->producerList.begin();
      it != this->producerList.end(); it++) {
    (*it)->dump(out);
  }
}

void ProducerOwner::addProducer(boost::shared_ptr<Producer> p) {
  this->producerList.push_back(p);
}

double ProducerOwner::notEnoughEnergyAction(double needed) {
  purchasedEnergy += needed;
  return needed;                                                                //TODO less or more or different?
}

void ProducerOwner::postStepAction(double energy) {
  if(energy > 40) tooMuchEnergyCounter++;                                       //TODO 40?
  else tooMuchEnergyCounter = 0;

  if(energy <= 0) addNewProducer();                                             //TODO <= x oder % oder ...

  if(producerList.size() > 1 &&
        tooMuchEnergyCounter > config::EnergyPlan::convertTime(0,30)) {         //TODO halbe stunde?
    removeProducer();
  }
}

void ProducerOwner::addNewProducer() {
  if(Simulation::getTime() > nextPossibleStart) {
    boost::shared_ptr<producer::Producer> p = DeviceFactory::getProducerInstance("windmill", "asdf", false);
    addProducer(p); //TODO id generieren, muss zeit zum anlaufen berücksichtigen
    nextPossibleStart = Simulation::getTime() + p->getStartupTime();            //TODO flexibler gestalten: momentan nur ein startup gleichzeitig möglich
  }
}

void ProducerOwner::removeProducer() {
  if(producerList.size() > 1) producerList.pop_back();                          // cannot remove last producer
}

}}} /* End of namespaces */
