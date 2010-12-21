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
  for(int i=numberOfProducers; i<numberOfProducers+numberOfConsumers; i++) getStandardConsumerOwner(i);  //TODO hier
  file << "  </medium>" << std::endl;
}

void ConfigBuilder::getStaticEnergyPlan(int start, int end, int rate) {
  file << "        <energyPlan type=\"static\" start=\"" << start << "\"";
  file << " end=\"" << end << "\"";
  file << " rate=\"" << rate << "\"";
  file << " />" << std::endl;
}

void ConfigBuilder::getDynamicEnergyPlan(int start, int end, int period, int highTime, int min, int max) {
  file << "        <energyPlan type=\"repeat\" start=\"" << start << "\"";
  file << " end=\"" << end << "\"";
  file << " period=\"" << period << "\"";
  file << " highTime=\"" << highTime << "\"";
  file << " lowEnergy=\"" << min << "\"";
  file << " highEnergy=\"" << max << "\"";
  file << " />" << std::endl;
}

// --------------------------------------------
// adapt
// --------------------------------------------

void ConfigBuilder::getStandardProducerOwner(int id) {
  file << "    <producerOwner id=\"" << id << "\">" << std::endl;
  getWindmill(id, 1);
  file << "    </producerOwner>" << std::endl;
}

void ConfigBuilder::getStandardConsumerOwner(int id) {
  file << "    <consumerOwner id=\"" << id << "\">" << std::endl;
  getStandardStaticConsumer(id, 1);
  getStandardDynamicConsumer(id, 2);
  file << "    </consumerOwner>" << std::endl;
}

// --------------------------------------------
// arbitrary
// --------------------------------------------

void ConfigBuilder::getWindmill(int id, int subid) {
  file << "      <producer id=\"" << id << "-" << subid << "\" " << "type=\"windmill\" />" << std::endl;
//  getStaticEnergyPlan(0, duration, productionRate); //TODO values
//  file << "      </producer>" << std::endl;
}

void ConfigBuilder::getStandardStaticConsumer(int id, int subid) {
  file << "      <consumer id=\"" << id << "-" << subid << "\" " << "type=\"fridge\">" << std::endl;
  getStaticEnergyPlan(0, duration, 3); //TODO values
  file << "      </consumer>" << std::endl;
}

void ConfigBuilder::getStandardDynamicConsumer(int id, int subid) {
  file << "      <consumer id=\"" << id << "-" << subid << "\" " << "type=\"fridge\">" << std::endl;
  getDynamicEnergyPlan(0, duration, 5, 3, 1, 10); //TODO values
  file << "      </consumer>" << std::endl;
}

void ConfigBuilder::buildConfig() {
  buildHull();
}

}
