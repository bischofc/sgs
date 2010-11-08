
#ifndef ENERGYEXCEPTION_H_
#define ENERGYEXCEPTION_H_

#include <exception>

namespace simulation {
namespace exception {

class EnergyException : public std::exception {
  const char* reason;

public:
  EnergyException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

} /* End of namespace simulation.exception */
} /* End of namespace simulation */

#endif /* ENERGYEXCEPTION_H_ */
