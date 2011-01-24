
#include "DeviceFactory.h"

#include "consumers/devices/Boiler.h"
#include "consumers/devices/Coffeemachine.h"
#include "consumers/devices/ComputerHigh.h"
#include "consumers/devices/ComputerLow.h"
#include "consumers/devices/ComputerMid.h"
#include "consumers/devices/Dishwasher.h"
#include "consumers/devices/Freezer.h"
#include "consumers/devices/Fridge.h"
#include "consumers/devices/Heater.h"
#include "consumers/devices/Kettle.h"
#include "consumers/devices/Light.h"
#include "consumers/devices/Microwave.h"
#include "consumers/devices/Oven.h"
#include "consumers/devices/Radio.h"
#include "consumers/devices/Stove.h"
#include "consumers/devices/Television.h"
#include "consumers/devices/Tumbler.h"
#include "consumers/devices/Washer.h"

#include "producers/devices/Windmill.h"

namespace simulation {
namespace endpoint {

boost::shared_ptr<consumer::Consumer> DeviceFactory::getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  if(type == "boiler") return boost::shared_ptr<consumer::Consumer>(new consumer::Boiler(id));
  else if(type == "coffeemachine") return boost::shared_ptr<consumer::Consumer>(new consumer::Coffeemachine(id));
  else if(type == "computerHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::ComputerHigh(id));
  else if(type == "computerLow") return boost::shared_ptr<consumer::Consumer>(new consumer::ComputerLow(id));
  else if(type == "computerMid") return boost::shared_ptr<consumer::Consumer>(new consumer::ComputerMid(id));
  else if(type == "dishwasher") return boost::shared_ptr<consumer::Consumer>(new consumer::Dishwasher(id));
  else if(type == "freezer") return boost::shared_ptr<consumer::Consumer>(new consumer::Freezer(id));
  else if(type == "fridge") return boost::shared_ptr<consumer::Consumer>(new consumer::Fridge(id));
  else if(type == "heater") return boost::shared_ptr<consumer::Consumer>(new consumer::Heater(id));
  else if(type == "kettle") return boost::shared_ptr<consumer::Consumer>(new consumer::Kettle(id));
  else if(type == "light") return boost::shared_ptr<consumer::Consumer>(new consumer::Light(id));
  else if(type == "microwave") return boost::shared_ptr<consumer::Consumer>(new consumer::Microwave(id));
  else if(type == "oven") return boost::shared_ptr<consumer::Consumer>(new consumer::Oven(id));
  else if(type == "radio") return boost::shared_ptr<consumer::Consumer>(new consumer::Radio(id));
  else if(type == "stove") return boost::shared_ptr<consumer::Consumer>(new consumer::Stove(id));
  else if(type == "television") return boost::shared_ptr<consumer::Consumer>(new consumer::Television(id));
  else if(type == "tumbler") return boost::shared_ptr<consumer::Consumer>(new consumer::Tumbler(id));
  else if(type == "washer") return boost::shared_ptr<consumer::Consumer>(new consumer::Washer(id));
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
