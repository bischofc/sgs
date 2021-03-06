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

#include "DeviceFactory.h"

#include "consumers/devices/Appliances.h"
#include "consumers/devices/BoilerHigh.h"
#include "consumers/devices/BoilerLow.h"
#include "consumers/devices/BoilerMid.h"
#include "consumers/devices/CoffeemachineHigh.h"
#include "consumers/devices/CoffeemachineLow.h"
#include "consumers/devices/ComputerHigh.h"
#include "consumers/devices/ComputerLow.h"
#include "consumers/devices/DishwasherHigh.h"
#include "consumers/devices/DishwasherLow.h"
#include "consumers/devices/DishwasherMid.h"
#include "consumers/devices/FreezerHigh.h"
#include "consumers/devices/FreezerLow.h"
#include "consumers/devices/FreezerMid.h"
#include "consumers/devices/FridgeHigh.h"
#include "consumers/devices/FridgeLow.h"
#include "consumers/devices/FridgeMid.h"
#include "consumers/devices/HeaterHigh.h"
#include "consumers/devices/HeaterLow.h"
#include "consumers/devices/KettleLow.h"
#include "consumers/devices/KettleHigh.h"
#include "consumers/devices/LightHigh.h"
#include "consumers/devices/LightLow.h"
#include "consumers/devices/MicrowaveLow.h"
#include "consumers/devices/MicrowaveHigh.h"
#include "consumers/devices/Oven.h"
#include "consumers/devices/Radio.h"
#include "consumers/devices/StandBy.h"
#include "consumers/devices/StoveHigh.h"
#include "consumers/devices/StoveLow.h"
#include "consumers/devices/TelevisionHigh.h"
#include "consumers/devices/TelevisionLow.h"
#include "consumers/devices/TumblerHigh.h"
#include "consumers/devices/TumblerLow.h"
#include "consumers/devices/TumblerMid.h"
#include "consumers/devices/Vacuum.h"
#include "consumers/devices/WasherHigh.h"
#include "consumers/devices/WasherLow.h"
#include "consumers/devices/WasherMid.h"

#include "producers/devices/Conventional.h"
#include "producers/devices/Solar.h"
#include "producers/devices/Windmill.h"

namespace simulation {
namespace endpoint {

boost::shared_ptr<consumer::Consumer> DeviceFactory::getConsumerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  if(type == "appliances") return boost::shared_ptr<consumer::Consumer>(new consumer::Appliances(id));
  else if(type == "boilerHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::BoilerHigh(id));
  else if(type == "boilerLow") return boost::shared_ptr<consumer::Consumer>(new consumer::BoilerLow(id));
  else if(type == "boilerMid") return boost::shared_ptr<consumer::Consumer>(new consumer::BoilerMid(id));
  else if(type == "coffeemachineHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::CoffeemachineHigh(id));
  else if(type == "coffeemachineLow") return boost::shared_ptr<consumer::Consumer>(new consumer::CoffeemachineLow(id));
  else if(type == "computerHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::ComputerHigh(id));
  else if(type == "computerLow") return boost::shared_ptr<consumer::Consumer>(new consumer::ComputerLow(id));
  else if(type == "dishwasherHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::DishwasherHigh(id));
  else if(type == "dishwasherLow") return boost::shared_ptr<consumer::Consumer>(new consumer::DishwasherLow(id));
  else if(type == "dishwasherMid") return boost::shared_ptr<consumer::Consumer>(new consumer::DishwasherMid(id));
  else if(type == "heaterHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::HeaterHigh(id));
  else if(type == "heaterLow") return boost::shared_ptr<consumer::Consumer>(new consumer::HeaterLow(id));
  else if(type == "kettleHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::KettleHigh(id));
  else if(type == "kettleLow") return boost::shared_ptr<consumer::Consumer>(new consumer::KettleLow(id));
  else if(type == "lightHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::LightHigh(id));
  else if(type == "lightLow") return boost::shared_ptr<consumer::Consumer>(new consumer::LightLow(id));
  else if(type == "microwaveHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::MicrowaveHigh(id));
  else if(type == "microwaveLow") return boost::shared_ptr<consumer::Consumer>(new consumer::MicrowaveLow(id));
  else if(type == "oven") return boost::shared_ptr<consumer::Consumer>(new consumer::Oven(id));
  else if(type == "radio") return boost::shared_ptr<consumer::Consumer>(new consumer::Radio(id));
  else if(type == "standby") return boost::shared_ptr<consumer::Consumer>(new consumer::StandBy(id));
  else if(type == "stoveHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::StoveHigh(id));
  else if(type == "stoveLow") return boost::shared_ptr<consumer::Consumer>(new consumer::StoveLow(id));
  else if(type == "televisionHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::TelevisionHigh(id));
  else if(type == "televisionLow") return boost::shared_ptr<consumer::Consumer>(new consumer::TelevisionLow(id));
  else if(type == "tumblerHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::TumblerHigh(id));
  else if(type == "tumblerLow") return boost::shared_ptr<consumer::Consumer>(new consumer::TumblerLow(id));
  else if(type == "tumblerMid") return boost::shared_ptr<consumer::Consumer>(new consumer::TumblerMid(id));
  else if(type == "vacuum") return boost::shared_ptr<consumer::Consumer>(new consumer::Vacuum(id));
  else if(type == "washerHigh") return boost::shared_ptr<consumer::Consumer>(new consumer::WasherHigh(id));
  else if(type == "washerLow") return boost::shared_ptr<consumer::Consumer>(new consumer::WasherLow(id));
  else if(type == "washerMid") return boost::shared_ptr<consumer::Consumer>(new consumer::WasherMid(id));
  else if(type == "freezer") {
    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.25) return boost::shared_ptr<consumer::Consumer>(new consumer::FreezerLow(id));
    else if(rand < 0.8) return boost::shared_ptr<consumer::Consumer>(new consumer::FreezerMid(id));
    else return boost::shared_ptr<consumer::Consumer>(new consumer::FreezerHigh(id));
  }
  else if(type == "fridge") {
    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.25) return boost::shared_ptr<consumer::Consumer>(new consumer::FridgeLow(id));
    else if(rand < 0.8) return boost::shared_ptr<consumer::Consumer>(new consumer::FridgeMid(id));
    else return boost::shared_ptr<consumer::Consumer>(new consumer::FridgeHigh(id));
  }
  else {
    std::string msg = "DeviceFactory: The consumer '" + type + "' does not exist. Please check configuration.";
    throw exception::NoSuchDeviceException(msg.c_str());
  }
}

boost::shared_ptr<producer::Producer> DeviceFactory::getProducerInstance(std::string type, std::string id) throw (exception::NoSuchDeviceException) {
  if(type == "conventional") return boost::shared_ptr<producer::Producer>(new producer::Conventional(id));
  else if(type == "solar") return boost::shared_ptr<producer::Producer>(new producer::Solar(id));
  else if(type == "windmill") return boost::shared_ptr<producer::Producer>(new producer::Windmill(id));
  else {
    std::string msg = "DeviceFactory: The producer '" + type + "' does not exist. Please check configuration.";
    throw exception::NoSuchDeviceException(msg.c_str());
  }
}

} // end of namespace simulation::endpoint
} // end of namespace simulation
