/*
Copyright (C) 2010 Christian Bischof (bischof.christian@gmail.com)
This file is part of "Smart Grid Simulator".

"Smart Grid Simulator" is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Smart Grid Simulator" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Smart Grid Simulator".  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef simulation_exception_domainException_h
#define simulation_exception_domainException_h

#include <exception>

namespace helper {
namespace exception {

class DomainException : public std::exception {
  const char* reason;

public:
  DomainException(const char* reason) {
    this->reason = reason;
  }

  const char* what() const throw() {
    return reason;
  }
};

}} /* End of namespaces */

#endif
