#include <ProducerOwner.h>

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  this->id = ownerId;
}

std::string ProducerOwner::getId() {
  return 0;
}

int ProducerOwner::getEnergy() throw (exception::EnergyException) {
  int energy = 0;

  std::vector< Producer * >::iterator it;
  for(it = this->producerList.begin(); it != this->producerList.end(); it++) {
    Producer * p = *it;
    energy += ((Producer *) *it)->getCurrentEnergy();
  }

  return energy;
}

void ProducerOwner::dump(std::ostringstream &out) {
  out << "    ProducerOwner-Id: " << this->id << std::endl;
  for(std::vector< Producer* >::iterator it = this->producerList.begin();
      it != this->producerList.end(); it++) {
    Producer * p = *it;
    p->dump(out);
  }
}

void ProducerOwner::addProducer(Producer * p) {
  this->producerList.push_back(p);
}

} /* End of namespace simulation::endpoint::producer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
