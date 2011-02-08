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

  //TODO test-consumer weg
  file << "    <type id=\"test-consumer\">" << std::endl;
  getConsumer("oven", 1);
  file << "    </type>" << std::endl;

  file << "    <type id=\"retiree-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("lightLow", 3);
  getConsumer("dishwasherLow", 4);
  getConsumer("oven", 5);
  getConsumer("coffeemachineLow", 6);
  getConsumer("microwave", 7);
  getConsumer("kettle", 8);
  getConsumer("washer", 9);
  getConsumer("tumbler", 10);
  getConsumer("heater", 11);
  getConsumer("boiler", 12);
  getConsumer("television", 13);
  getConsumer("computerLow", 14);
  getConsumer("stove", 15);
  getConsumer("radio", 16);
  getConsumer("standby", 17);
  file << "    </type>" << std::endl;

  file << "    <type id=\"shift-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("lightHigh", 3);
  getConsumer("dishwasherMid", 4);
  getConsumer("oven", 5);
  getConsumer("coffeemachineHigh", 6);
  getConsumer("microwave", 7);
  getConsumer("kettle", 8);
  getConsumer("washer", 9);
  getConsumer("tumbler", 10);
  getConsumer("heater", 11);
  getConsumer("boiler", 12);
  getConsumer("television", 13);
  getConsumer("computerMid", 14);
  getConsumer("stove", 15);
  getConsumer("radio", 16);
  getConsumer("standby", 17);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam2-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("lightLow", 3);
  getConsumer("dishwasherMid", 4);
  getConsumer("oven", 5);
  getConsumer("coffeemachineLow", 6);
  getConsumer("microwave", 7);
  getConsumer("kettle", 8);
  getConsumer("washer", 9);
  getConsumer("tumbler", 10);
  getConsumer("heater", 11);
  getConsumer("boiler", 12);
  getConsumer("television", 13);
  getConsumer("computerLow", 14);
  getConsumer("stove", 15);
  getConsumer("radio", 16);
  getConsumer("standby", 17);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam4-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("lightHigh", 3);
  getConsumer("dishwasherMid", 4);
  getConsumer("oven", 5);
  getConsumer("coffeemachineLow", 6);
  getConsumer("microwave", 7);
  getConsumer("kettle", 8);
  getConsumer("washer", 9);
  getConsumer("tumbler", 10);
  getConsumer("heater", 11);
  getConsumer("boiler", 12);
  getConsumer("television", 13);
  getConsumer("computerMid", 14);
  getConsumer("stove", 15);
  getConsumer("radio", 16);
  getConsumer("standby", 17);
  file << "    </type>" << std::endl;

  file << "    <type id=\"fam5-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("freezer", 2);
  getConsumer("lightHigh", 3);
  getConsumer("dishwasherHigh", 4);
  getConsumer("oven", 5);
  getConsumer("coffeemachineLow", 6);
  getConsumer("microwave", 7);
  getConsumer("kettle", 8);
  getConsumer("washer", 9);
  getConsumer("tumbler", 10);
  getConsumer("heater", 11);
  getConsumer("boiler", 12);
  getConsumer("television", 13);
  getConsumer("computerHigh", 14);
  getConsumer("stove", 15);
  getConsumer("radio", 16);
  getConsumer("standby", 17);
  file << "    </type>" << std::endl;

  file << "  </endpoint-types>" << std::endl;
}

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "    <producerOwner o-id=\"" << id << "\" type=\"standard-producer\" />" << std::endl;
}

void ConfigBuilder::getConsumerOwner(int id) {
  int choice = helper::RandomNumbers::getRandom(1, 5);
//  choice = 6;
  switch(choice) {
    case 1:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"retiree-consumer\" />" << std::endl;
      break;
    case 2:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"shift-consumer\" />" << std::endl;
      break;
    case 3:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam2-consumer\" />" << std::endl;
      break;
    case 4:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam4-consumer\" />" << std::endl;
      break;
    case 5:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"fam5-consumer\" />" << std::endl;
      break;
    default:
      file << "    <consumerOwner o-id=\"" << id << "\" type=\"test-consumer\" />" << std::endl;
      break;
  }
}

}
