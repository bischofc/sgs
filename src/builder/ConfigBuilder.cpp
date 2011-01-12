#include "ConfigBuilder.h"

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
//  getConfig();                                                                //TODO entfernen -> auch input arguments
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
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getStandardConsumerOwner(i);  //TODO: mix von consumer arten
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

  file << "    <type id=\"standard-consumer\">" << std::endl;
  getConsumer("fridge", 1);
  getConsumer("kettle", 2);
  getConsumer("radio", 3);
  getConsumer("television", 4);
  getConsumer("ventilator", 5);
  getConsumer("stove",  6);
  getConsumer("light", 7);
  file << "    </type>" << std::endl;

  file << "  </endpoint-types>" << std::endl;
}

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "    <producerOwner o-id=\"" << id << "\" type=\"standard-producer\" />" << std::endl;
}

void ConfigBuilder::getStandardConsumerOwner(int id) {
  file << "    <consumerOwner o-id=\"" << id << "\" type=\"standard-consumer\" />" << std::endl;
}

}
