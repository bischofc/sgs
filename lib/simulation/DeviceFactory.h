
#ifndef simulation_endpoint_deviceFactory_h
#define simulation_endpoint_deviceFactory_h

#include "NoSuchDeviceException.h"
#include "Consumer.h"
#include "Producer.h"

namespace simulation {
namespace endpoint {

class DeviceFactory {
  DeviceFactory();
  static void throwException(std::string device);

public:
  static consumer::Consumer * getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException);
  static producer::Producer * getProducerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException);
  virtual ~DeviceFactory();
};

} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif /* simulation_endpoint_deviceFactory_h */
