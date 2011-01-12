
#include "DeviceFactory.h"

#include "consumers/devices/Kettle.h"
#include "consumers/devices/Fridge.h"
#include "consumers/devices/Light.h"
#include "consumers/devices/Radio.h"
#include "consumers/devices/Stove.h"
#include "consumers/devices/Television.h"
#include "consumers/devices/Ventilator.h"

#include "producers/devices/Windmill.h"

namespace simulation {
namespace endpoint {

boost::shared_ptr<consumer::Consumer> DeviceFactory::getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  if(type == "fridge") return boost::shared_ptr<consumer::Consumer>(new consumer::Fridge(id));
  else if(type == "kettle") return boost::shared_ptr<consumer::Consumer>(new consumer::Kettle(id));
  else if(type == "radio") return boost::shared_ptr<consumer::Consumer>(new consumer::Radio(id));
  else if(type == "television") return boost::shared_ptr<consumer::Consumer>(new consumer::Television(id));
  else if(type == "stove") return boost::shared_ptr<consumer::Consumer>(new consumer::Stove(id));
  else if(type == "light") return boost::shared_ptr<consumer::Consumer>(new consumer::Light(id));
  else if(type == "ventilator") return boost::shared_ptr<consumer::Consumer>(new consumer::Ventilator(id));
  else {
    std::string msg = "DeviceFactory: The consumer '" + type + "' does not exist. Please check configuration.";
    throw exception::NoSuchDeviceException(msg.c_str());
  }
}

boost::shared_ptr<producer::Producer> DeviceFactory::getProducerInstance(std::string type, std::string id, bool startInstantly) throw (exception::NoSuchDeviceException) {
  if(type == "windmill") return boost::shared_ptr<producer::Producer>(new producer::Windmill(id, startInstantly));
  else {
    std::string msg = "DeviceFactory: The producer '" + type + "' does not exist. Please check configuration.";
    throw exception::NoSuchDeviceException(msg.c_str());
  }
}

} // end of namespace simulation::endpoint
} // end of namespace simulation
