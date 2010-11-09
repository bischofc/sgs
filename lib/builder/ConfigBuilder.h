#ifndef CONFIGBUILDER_H_
#define CONFIGBUILDER_H_

#include <string>
#include <fstream>

namespace builder {

class ConfigBuilder {
  std::ofstream file;
  std::string mediumName;
  int numberOfProducers;
  int productionRate;
  int numberOfConsumers;

  // build standards
  // ---------------
  void buildHull();
  void getStandardMedium();
  void getStandardProducerOwner(int);
  void getStandardProducer(int, int);
  void getStandardConsumerOwner(int);
  void getStandardConsumer(int, int);
  void getStaticEnergyPlan(int, int, int);
  void getDynamicEnergyPlan(int, int, int, int, int, int);

public:
  ConfigBuilder(const char *, std::string, int, int, int);
  void buildConfig();
  ~ConfigBuilder();
};

}

#endif /* CONFIGBUILDER_H_ */
