
#include "ConsumerOwner.h"

namespace simulation {
namespace endpoint {
namespace consumer {

ConsumerOwner::ConsumerOwner(std::string ownerId) {
  this->id = ownerId;
}

std::string ConsumerOwner::getId() {
  return 0;
}

double ConsumerOwner::getEnergy() throw (exception::EnergyException){
  double energy = 0.0;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerList.begin();
                  it != this->consumerList.end(); it++) {
    energy += (*it)->getCurrentEnergy();
  }
  return energy;
}

void ConsumerOwner::adjustLoad(std::vector<int> adjustment) {
  //TODO hier weiter
}

void ConsumerOwner::dump(std::ostringstream &out) {
  out << "    ConsumerOwner-Id: " << this->id << std::endl;
  for(std::vector< boost::shared_ptr<Consumer> >::iterator it = this->consumerList.begin();
      it != this->consumerList.end(); it++) {
    (*it)->dump(out);
  }
}

void ConsumerOwner::addConsumer(boost::shared_ptr<Consumer> c) {
  this->consumerList.push_back(c);
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
