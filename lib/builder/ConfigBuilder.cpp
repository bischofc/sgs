#include "ConfigBuilder.h"

namespace builder {

ConfigBuilder::ConfigBuilder(const char * fileName, int duration,
//                int producerNo, int productionRate,
                int consumerNo,
                std::string mediumName) {
  this->duration = duration;
//  this->numberOfProducers = producerNo;
  this->numberOfProducers = 1;
  this->productionRate = productionRate;
  this->numberOfConsumers = consumerNo;
  this->mediumName = mediumName;
  file.open(fileName); //todo check if exists, valid path, ...?
}

ConfigBuilder::~ConfigBuilder() {
  file.close();
}

void ConfigBuilder::buildHull() {
  file << "<?xml version=\"1.0\" ?>" << std::endl;
  file << "<!DOCTYPE simulation SYSTEM \"config.dtd\">" << std::endl;
  file << "<simulation>" << std::endl;
  getConfigTag();
  getStandardMedium();
  file << "</simulation>" << std::endl;
}

void ConfigBuilder::getConfigTag() {
  file << "  <config>" << std::endl;
  file << "    <simDesc duration=\"" << duration << "\" />" << std::endl;
  file << "  </config>" << std::endl;
}

void ConfigBuilder::getStandardMedium() {
  file << "  <medium name=\"" << mediumName << "\">" << std::endl;
  for(int i=0; i<numberOfProducers; i++) getStandardProducerOwner(i);
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getStandardConsumerOwner(i);  //TODO: mix von consumer arten
  file << "  </medium>" << std::endl;
}

// @type: element of {windmill, ... } see implemented producers
// also take a look at SimulationBuilder since it builds the simulation
void ConfigBuilder::getProducer(std::string type, int id, int subid) {
  file << "      <producer id=\"" << id << "-" << subid << "\" " << "type=\"" << type << "\" />" << std::endl;
}

// @type: element of {fridge, ... } see implemented consumers
// also take a look at SimulationBuilder since it builds the simulation
void ConfigBuilder::getConsumer(std::string type, int id, int subid) {
  file << "      <consumer id=\"" << id << "-" << subid << "\" " << "type=\"" << type << "\" />" << std::endl;
}

// --------------------------------------------
// adapt
// --------------------------------------------

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "    <producerOwner id=\"" << id << "\">" << std::endl;
  getProducer("windmill", id, 1);
  file << "    </producerOwner>" << std::endl;
}

void ConfigBuilder::getStandardConsumerOwner(int id) {
  file << "    <consumerOwner id=\"" << id << "\">" << std::endl;
  getConsumer("fridge", id, 1);
//  getConsumer("fridge", id, 2);
  file << "    </consumerOwner>" << std::endl;
}

// --------------------------------------------
// arbitrary
// --------------------------------------------

void ConfigBuilder::buildConfig() {
  buildHull();
}

}
