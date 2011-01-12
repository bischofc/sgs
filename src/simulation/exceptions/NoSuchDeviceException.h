
#ifndef simulation_exception_noSuchDeviceException_h
#define simulation_exception_noSuchDeviceException_h

#include <exception>

namespace simulation {
namespace exception {

class NoSuchDeviceException : public std::exception {
  const char* reason;

public:
  NoSuchDeviceException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

} /* End of namespace simulation.exception */
} /* End of namespace simulation */

#endif /* simulation_exception_noSuchDeviceException_h */
