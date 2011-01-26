#include "ConfigBuilder.h"
#include "RandomNumbers.h"

namespace builder {

ConfigBuilder::ConfigBuilder(const char * fileName, int duration, int resolution,
//                int producerNo, int productionRate,
                int consumerNo,
                std::string mediumName) {
  this->duration = duration;
  this->resolution = resolution;
  this->numberOfProducers = 1;
  this->numberOfConsumers = consumerNo;
  this->mediumName = mediumName;
  file.open(fileName); //todo check if exists, valid path, ...?
}

ConfigBuilder::~ConfigBuilder() {
  file.close();
}

void ConfigBuilder::buildConfig() {
  buildHull();
}

void ConfigBuilder::buildHull() {
  file << "<?xml version=\"1.0\" ?>" << std::endl;
  file << "<!DOCTYPE simulation SYSTEM \"config.dtd\">" << std::endl;
  file << "<simulation>" << std::endl;
  getConfig();                                                                //TODO entfernen -> auch input arguments
  getEndpointTypes();
  getStandardMedium();
  file << "</simulation>" << std::endl;
}

void ConfigBuilder::getConfig() {
  file << "  <config>" << std::endl;
  file << "    <simDesc duration=\"" << duration << "\" " << "resolution=\"" << resolution << "\" />" << std::endl;
  file << "  </config>" << std::endl;
}

void ConfigBuilder::getStandardMedium() {
  file << "  <medium m-id=\"" << mediumName << "\">" << std::endl;
  for(int i=0; i<numberOfProducers; i++) getStandardProducerOwner(i);
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getConsumerOwner(i);  //TODO: mix von consumer arten
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
  file << "  <endpoint-types>" << std::endl;

  file << "    <type id=\"standard-producer\">" << std::endl;
  getProducer("windmill", 1);
  file << "    </type>" << std::endl;

//  file << "    <type id=\"test-consumer\">" << std::endl;
//  getConsumer("washer", 1);
//  getConsumer("tumbler", 2);
//  file << "    </type>" << std::endl;

  file << "    <type id=\"student-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("light", 3);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerHigh", 11);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "    <type id=\"single-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("light", 3);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerHigh", 11);
  getConsumer("washer", 14);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "    <type id=\"large-one-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("light", 3);
  getConsumer("oven", 4);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerMid", 11);
  getConsumer("tumbler", 12);
  getConsumer("dishwasher", 13);
  getConsumer("washer", 14);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "    <type id=\"large-multi-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("light", 3);
  getConsumer("oven", 4);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerMid", 11);
  getConsumer("dishwasher", 13);
  getConsumer("washer", 14);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "    <type id=\"small-one-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("light", 3);
  getConsumer("oven", 4);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerLow", 11);
  getConsumer("tumbler", 12);
  getConsumer("dishwasher", 13);
  getConsumer("washer", 14);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "    <type id=\"small-multi-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("light", 3);
  getConsumer("oven", 4);
  getConsumer("microwave", 5);
  getConsumer("coffeemachine", 6);
  getConsumer("kettle", 7);
  getConsumer("stove",  8);
  getConsumer("radio", 9);
  getConsumer("television", 10);
  getConsumer("computerLow", 11);
  getConsumer("tumbler", 12);
  getConsumer("dishwasher", 13);
  getConsumer("washer", 14);
  getConsumer("heater", 15);
  getConsumer("boiler", 16);
  file << "    </type>" << std::endl;

  file << "  </endpoint-types>" << std::endl;
}

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "    <producerOwner o-id=\"" << id << "\" type=\"standard-producer\" />" << std::endl;
}

void ConfigBuilder::getConsumerOwner(int id) {
  int choice = helper::RandomNumbers::getRandom(1, 6);
//  choice = 7
  switch(choice) {
    case 1:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"student-consumer\" />" << std::endl;
      break;
    case 2:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"single-consumer\" />" << std::endl;
      break;
    case 3:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"large-one-consumer\" />" << std::endl;
      break;
    case 4:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"large-multi-consumer\" />" << std::endl;
      break;
    case 5:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"small-one-consumer\" />" << std::endl;
      break;
    case 6:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"small-multi-consumer\" />" << std::endl;
      break;
    default:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"test-consumer\" />" << std::endl;
      break;
  }
}

}
