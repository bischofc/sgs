#include "Medium.h"
#include "producers/ProducerOwner.h"
#include "consumers/ConsumerOwner.h"
#include "Simulation.h"

namespace simulation {
namespace medium {

Medium::Medium(std::string name) {
  energy = 0;
  producerOwnerSet = false;
  this->name = name;
}

void Medium::registerConsumerOwner(boost::shared_ptr<endpoint::consumer::ConsumerOwner> co) {
  this->consumerOwnerList.push_back(co);
}

void Medium::registerProducerOwner(boost::shared_ptr<endpoint::producer::ProducerOwner> po) {
  if(producerOwnerSet) {
    throw exception::ParserException("Producer cannot be registered, one already exists. Check config file.");
  } else {
    producerOwner = po;
    producerOwnerSet = true;
  }
}

void Medium::oneStep() throw (exception::EnergyException) {
  // check if producer exists
  if(!producerOwnerSet) {
    throw exception::NoSuchDeviceException("No producer owner found. Check config file");   //TODO exit!
  }

  // initialize step
  energy = 0;

  // get load adjustment from producer owner
  loadAdjustment = producerOwner->getLoadAdjustment(getNumberOfConsumers());

  // send load adjustment if available and check energy consumption
  for(std::vector< boost::shared_ptr<endpoint::consumer::ConsumerOwner> >::iterator it = this->consumerOwnerList.begin();
                  it < this->consumerOwnerList.end(); it++) {
    boost::shared_ptr<endpoint::consumer::ConsumerOwner> e = *it;
    if(!loadAdjustment.empty()) e->adjustLoad(loadAdjustment);
    double tmp = e->getEnergy();
    energy += tmp;
  }
}

void Medium::dump(std::ostringstream &out) {
  out << "  Medium (" << this->name << ") start..." << std::endl;
  for(std::vector< boost::shared_ptr<endpoint::consumer::ConsumerOwner> >::iterator it = this->consumerOwnerList.begin();
      it != this->consumerOwnerList.end(); it++) {
    (*it)->dump(out);
  }
  out << "  Medium end." << std::endl;
}

double Medium::getCurrentEnergy() {
  return energy;
}

int Medium::getNumberOfConsumers() {
  return consumerOwnerList.size();
}


} /* End of namespace simulation::medium */
} /* End of namespace simulation */
