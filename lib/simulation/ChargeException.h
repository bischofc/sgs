
#ifndef CHARGEEXCEPTION_H_
#define CHARGEEXCEPTION_H_

#include <exception>

namespace simulation {
namespace exception {

class ChargeException : public std::exception {
  const char* reason;

public:
  ChargeException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

} /* End of namespace simulation.exception */
} /* End of namespace simulation */

#endif /* CHARGEEXCEPTION_H_ */
