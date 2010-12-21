
#ifndef simulation_exception_parserException_h
#define simulation_exception_parserException_h

#include <exception>

namespace simulation {
namespace exception {

class ParserException : public std::exception {
  const char* reason;

public:
  ParserException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

} /* End of namespace simulation.exception */
} /* End of namespace simulation */

#endif /* simulation_exception_parserException_h */
