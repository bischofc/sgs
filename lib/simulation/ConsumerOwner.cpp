#include <ConsumerOwner.h>

namespace simulation {
namespace endpoint {
namespace consumer {

ConsumerOwner::ConsumerOwner(std::string ownerId) {
  this->id = ownerId;
}

std::string ConsumerOwner::getId() {
  return 0;
}

int ConsumerOwner::getEnergy() throw (exception::EnergyException){
  int energy = 0;

  std::vector< Consumer * >::iterator it;
  for(it = this->consumerList.begin(); it != this->consumerList.end(); it++) {
    energy -= ((Consumer *) *it)->getCurrentEnergy();
  }

  return energy;
}

void ConsumerOwner::dump(std::ostringstream &out) {
  out << "    ConsumerOwner-Id: " << this->id << std::endl;
  for(std::vector< Consumer* >::iterator it = this->consumerList.begin();
      it != this->consumerList.end(); it++) {
    Consumer * c = *it;
    c->dump(out);
  }
}

void ConsumerOwner::addConsumer(Consumer * c) {
  this->consumerList.push_back(c);
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
