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


#ifndef simulation_endpoint_deviceFactory_h
#define simulation_endpoint_deviceFactory_h

#include <boost/shared_ptr.hpp>

#include "exceptions/NoSuchDeviceException.h"
#include "consumers/Consumer.h"
#include "producers/Producer.h"

namespace simulation {
namespace endpoint {

class DeviceFactory {
  DeviceFactory();
  static void throwException(std::string device);

public:
  static boost::shared_ptr<consumer::Consumer> getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException);
  static boost::shared_ptr<producer::Producer> getProducerInstance(std::string type, std::string id, bool startInstantly) throw (exception::NoSuchDeviceException);
  virtual ~DeviceFactory();
};

} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif /* simulation_endpoint_deviceFactory_h */
