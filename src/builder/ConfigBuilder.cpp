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

#include <sys/stat.h>
#include <iostream>
#include "ConfigBuilder.h"
#include "RandomNumbers.h"
#include "exceptions/IOException.h"

//#define testrun

namespace builder {

ConfigBuilder::ConfigBuilder(const char * fileName, int duration, int consumerNo,
                std::string mediumName) {
  this->duration = duration;
  this->numberOfProducers = 1;
  this->numberOfConsumers = consumerNo;
  this->mediumName = mediumName;
  openFile(fileName);
}

void ConfigBuilder::openFile(const char * fileName) {
  struct stat fileStat;
  int intStat;
  intStat = stat(fileName, &fileStat);
  if(intStat == 0) {
    std::string answer;
    std::cout << "File exists. Overwrite? [y/N]: ";
    std::cin >> answer;
    if(answer == "y" || answer == "Y") {
      std::cout << "Overwrite existing file" << std::endl;
      file.open(fileName);
      return;
    }
    std::cout << "Keep existing file" << std::endl;
  } else file.open(fileName);
}

ConfigBuilder::~ConfigBuilder() {
  file.close();
}

void ConfigBuilder::buildConfig() {
  if(file.is_open()) buildHull();
}

void ConfigBuilder::buildHull() {
  file << "<?xml version=\"1.0\" ?>" << std::endl;
  file << "<!DOCTYPE simulation SYSTEM \"config.dtd\">" << std::endl;
  file << "<simulation>" << std::endl;
  getConfig();
  getEndpointTypes();
  getStandardMedium();
  file << "</simulation>" << std::endl;
}

void ConfigBuilder::getConfig() {
  file << "  <config>" << std::endl;
  file << "    <simDesc duration=\"" << duration << "\" />" << std::endl;
  file << "  </config>" << std::endl;
}

void ConfigBuilder::getStandardMedium() {
  file << "  <medium m-id=\"" << mediumName << "\">" << std::endl;
  for(int i=0; i<numberOfProducers; i++) getProducerOwner(i);
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getConsumerOwner(i);
  file << "  </medium>" << std::endl;
}


// @type: element of {windmill, ... } see implemented producers
// also take a look at SimulationBuilder since it builds the simulation
void ConfigBuilder::getProducer(std::string type, int id) {
  file << "      <producer d-id=\"" << id << "\" " << "type=\"" << type << "\" />" << std::endl;
}

// @type: element of {fridge, ... } see implemented consumers
// also take a look at SimulationBuilder since it builds the simulation
void ConfigBuilder::getConsumer(std::string type, int id) {
  file << "      <consumer d-id=\"" << id << "\" " << "type=\"" << type << "\" />" << std::endl;
}

// --------------------------------------------
// adapt
// --------------------------------------------

void ConfigBuilder::getEndpointTypes() {
  int i = 1;

  file << "  <endpoint-types>" << std::endl;

  file << "    <type id=\"standard-producer\">" << std::endl;
  getProducer("conventional", i++);
  getProducer("solar", i++);
  getProducer("windmill", i++);
  file << "    </type>" << std::endl;

  file << "    <type id=\"retiree-consumer\">" << std::endl;
  i = 1;
  getConsumer("appliances", i++);
  getConsumer("fridge", i++);
  getConsumer("freezer", i++);
  getConsumer("lightLow", i++);
  getConsumer("dishwasherLow", i++);
  getConsumer("oven", i++);
  getConsumer("coffeemachineLow", i++);
  getConsumer("microwaveLow", i++);
  getConsumer("kettleLow", i++);
  getConsumer("washerLow", i++);
  getConsumer("tumblerLow", i++);
  getConsumer("heaterHigh", i++);
  getConsumer("boilerLow", i++);
  getConsumer("televisionHigh", i++);
  getConsumer("computerLow", i++);
  getConsumer("stoveLow", i++);
  getConsumer("radio", i++);
  getConsumer("standby", i++);
  getConsumer("vacuum", i++);
  file << "    </type>" << std::endl;

  file << "    <type id=\"shift-consumer\">" << std::endl;
  i = 1;
  getConsumer("appliances", i++);
  getConsumer("fridge", i++);
  getConsumer("freezer", i++);
  getConsumer("lightHigh", i++);
  getConsumer("dishwasherMid", i++);
  getConsumer("oven", i++);
  getConsumer("coffeemachineHigh", i++);
  getConsumer("microwaveHigh", i++);
  getConsumer("kettleHigh", i++);
  getConsumer("washerMid", i++);
  getConsumer("tumblerMid", i++);
  getConsumer("heaterHigh", i++);
  getConsumer("boilerMid", i++);
  getConsumer("televisionHigh", i++);
  getConsumer("computerHigh", i++);
  getConsumer("stoveHigh", i++);
  getConsumer("radio", i++);
  getConsumer("standby", i++);
  getConsumer("vacuum", i++);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam2-consumer\">" << std::endl;
  i = 1;
  getConsumer("appliances", i++);
  getConsumer("fridge", i++);
  getConsumer("freezer", i++);
  getConsumer("lightLow", i++);
  getConsumer("dishwasherMid", i++);
  getConsumer("oven", i++);
  getConsumer("coffeemachineLow", i++);
  getConsumer("microwaveLow", i++);
  getConsumer("kettleLow", i++);
  getConsumer("washerLow", i++);
  getConsumer("tumblerLow", i++);
  getConsumer("heaterLow", i++);
  getConsumer("boilerMid", i++);
  getConsumer("televisionLow", i++);
  getConsumer("computerLow", i++);
  getConsumer("stoveLow", i++);
  getConsumer("radio", i++);
  getConsumer("standby", i++);
  getConsumer("vacuum", i++);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam4-consumer\">" << std::endl;
  i = 1;
  getConsumer("appliances", i++);
  getConsumer("fridge", i++);
  getConsumer("freezer", i++);
  getConsumer("lightHigh", i++);
  getConsumer("dishwasherMid", i++);
  getConsumer("oven", i++);
  getConsumer("coffeemachineLow", i++);
  getConsumer("microwaveLow", i++);
  getConsumer("kettleLow", i++);
  getConsumer("washerMid", i++);
  getConsumer("tumblerMid", i++);
  getConsumer("heaterHigh", i++);
  getConsumer("boilerMid", i++);
  getConsumer("televisionHigh", i++);
  getConsumer("computerHigh", i++);
  getConsumer("stoveHigh", i++);
  getConsumer("radio", i++);
  getConsumer("standby", i++);
  getConsumer("vacuum", i++);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam5-consumer\">" << std::endl;
  i = 1;
  getConsumer("appliances", i++);
  getConsumer("fridge", i++);
  getConsumer("freezer", i++);
  getConsumer("lightHigh", i++);
  getConsumer("dishwasherHigh", i++);
  getConsumer("oven", i++);
  getConsumer("coffeemachineLow", i++);
  getConsumer("microwaveLow", i++);
  getConsumer("kettleHigh", i++);
  getConsumer("washerHigh", i++);
  getConsumer("tumblerHigh", i++);
  getConsumer("heaterHigh", i++);
  getConsumer("boilerHigh", i++);
  getConsumer("televisionHigh", i++);
  getConsumer("computerHigh", i++);
  getConsumer("stoveHigh", i++);
  getConsumer("radio", i++);
  getConsumer("standby", i++);
  getConsumer("vacuum", i++);
  file << "    </type>" << std::endl;

#ifdef testrun
  file << "    <type id=\"test-consumer\">" << std::endl;
  i = 1;
  getConsumer("washerHigh", i++);
  file << "    </type>" << std::endl;
#endif

  file << "  </endpoint-types>" << std::endl;
}

void ConfigBuilder::getProducerOwner(int id) {
  file << "    <producerOwner o-id=\"" << id << "\" type=\"standard-producer\" />" << std::endl;
}

void ConfigBuilder::getConsumerOwner(int id) {
  double choice = helper::RandomNumbers::getRandom();

#ifdef testrun
  choice = 2;
#endif

  if(choice < 0.23) file << "    <consumerOwner o-id=\"" << id << "\" type=\"retiree-consumer\" />" << std::endl;
  else if(choice < 0.30) file << "    <consumerOwner o-id=\"" << id << "\" type=\"shift-consumer\" />" << std::endl;
  else if(choice < 0.77) file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam2-consumer\" />" << std::endl;
  else if(choice < 0.97) file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam4-consumer\" />" << std::endl;
  else if(choice <= 1) file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam5-consumer\" />" << std::endl;
  else file << "    <consumerOwner o-id=\"" << id << "\" type=\"test-consumer\" />" << std::endl;
}

}
