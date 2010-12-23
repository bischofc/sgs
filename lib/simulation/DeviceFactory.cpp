
#include "DeviceFactory.h"

namespace simulation {
namespace endpoint {

consumer::Consumer * DeviceFactory::getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  consumer::Consumer * consumer;

  // consumers
  if(type == "fridge") consumer = new consumer::Fridge(id);
  else if(type == "cattle") consumer = new consumer::Cattle(id);

  // if not defined -> throw exception
  else throwException(type);
  return consumer;
}

producer::Producer * DeviceFactory::getProducerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  producer::Producer * producer;

  // producers
  if(type == "windmill") producer = new producer::Windmill(id);

  // if not defined -> throw exception
  else throwException(type);
  return producer;
}

void DeviceFactory::throwException(std::string device) {
  std::string msg = "DeviceFactory: The device '" + device + "' does not exist. Please check configuration.";
  throw exception::NoSuchDeviceException(msg.c_str());
}

} // end of namespace simulation::endpoint
} // end of namespace simulation
