
#ifndef simulation_exception_energyException_h
#define simulation_exception_energyException_h

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

#endif /* simulation_exception_energyException_h */
