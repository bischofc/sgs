
#ifndef PARSEREXCEPTION_H_
#define PARSEREXCEPTION_H_

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

#endif /* PARSEREXCEPTION_H_ */
