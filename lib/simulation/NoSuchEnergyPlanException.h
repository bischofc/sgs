
#ifndef NOSUCHENERGYPLANEXCEPTION_H_
#define NOSUCHENERGYPLANEXCEPTION_H_

#include <exception>

namespace simulation {
namespace exception {

class NoSuchEnergyPlanException : public std::exception {
  const char* reason;

public:
  NoSuchEnergyPlanException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

} /* End of namespace simulation.exception */
} /* End of namespace simulation */

#endif /* NOSUCHENERGYPLANEXCEPTION_H_ */
