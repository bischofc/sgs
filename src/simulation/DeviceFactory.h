
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
