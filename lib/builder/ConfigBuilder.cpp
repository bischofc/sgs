#include "ConfigBuilder.h"

namespace builder {

ConfigBuilder::ConfigBuilder(const char * fileName, std::string mediumName,
                int producerNo, int productionRate, int consumerNo) {
  this->mediumName = mediumName;
  this->numberOfProducers = producerNo;
  this->productionRate = productionRate;
  this->numberOfConsumers = consumerNo;
  file.open(fileName); //todo check if exists, valid path, ...?
}

ConfigBuilder::~ConfigBuilder() {
  file.close();
}

void ConfigBuilder::buildHull() {
  file << "<?xml version=\"1.0\" ?>" << std::endl;
  file << "<!DOCTYPE medium SYSTEM \"config.dtd\">" << std::endl;
  getStandardMedium();
}

void ConfigBuilder::getStandardMedium() {
  file << "<medium name= \"" << mediumName << "\">" << std::endl;
  for(int i=0; i<numberOfProducers; i++) getStandardProducerOwner(i);
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getStandardConsumerOwner(i);
  file << "</medium>" << std::endl;
}

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "  <producerOwner id=\"" << id << "\">" << std::endl;
  getStandardProducer(id, 1);
  file << "  </producerOwner>" << std::endl;
}

void ConfigBuilder::getStandardProducer(int id, int subid) {
  file << "    <producer id=\"" << id << "-" << subid << "\" " << "type=\"windmill\">" << std::endl;
  getStaticEnergyPlan(0, 10, 2);
  file << "    </producer>" << std::endl;
}

void ConfigBuilder::getStandardConsumerOwner(int id) {
  file << "  <consumerOwner id=\"" << id << "\">" << std::endl;
  getStandardConsumer(id, 1);
  getStandardConsumer(id, 2);
  file << "  </consumerOwner>" << std::endl;
}

void ConfigBuilder::getStandardConsumer(int id, int subid) {
  file << "    <consumer id=\"" << id << "-" << subid << "\" " << "type=\"fridge\">" << std::endl;
  getDynamicEnergyPlan(0, 10, 5, 3, 1, 10);
  file << "    </consumer>" << std::endl;
}

void ConfigBuilder::getStaticEnergyPlan(int start, int end, int rate) {
  file << "      <energyPlan type=\"repeat\" start=\"" << start << "\"";
  file << " end=\"" << end << "\"";
  file << " rate=\"" << rate << "\"";
  file << " />" << std::endl;
}

void ConfigBuilder::getDynamicEnergyPlan(int start, int end, int period, int highTime, int min, int max) {
  file << "      <energyPlan type=\"repeat\" start=\"" << start << "\"";
  file << " end=\"" << end << "\"";
  file << " period=\"" << period << "\"";
  file << " highTime=\"" << highTime << "\"";
  file << " lowEnergy=\"" << min << "\"";
  file << " highEnergy=\"" << max << "\"";
  file << " />" << std::endl;
}

void ConfigBuilder::buildConfig() {
  buildHull();
}

}
