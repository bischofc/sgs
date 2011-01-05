
#ifndef simulation_endpoint_deviceFactory_h
#define simulation_endpoint_deviceFactory_h

#include "exceptions/NoSuchDeviceException.h"
#include "consumers/Consumer.h"
#include "producers/Producer.h"

namespace simulation {
namespace endpoint {

class DeviceFactory {
  DeviceFactory();
  static void throwException(std::string device);

public:
  static consumer::Consumer * getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException);
  static producer::Producer * getProducerInstance(std::string type, std::string id, bool startInstantly) throw (exception::NoSuchDeviceException);
  virtual ~DeviceFactory();
};

} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif /* simulation_endpoint_deviceFactory_h */
