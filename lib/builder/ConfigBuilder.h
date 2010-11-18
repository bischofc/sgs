#ifndef CONFIGBUILDER_H_
#define CONFIGBUILDER_H_

#include <string>
#include <fstream>

namespace builder {

class ConfigBuilder {
  std::ofstream file;
  std::string mediumName;
  int duration;
  int numberOfProducers;
  int productionRate;
  int numberOfConsumers;

  // build standards
  // ---------------
  void buildHull();
  void getConfigTag();
  void getStandardMedium();
  void getStandardProducerOwner(int);
  void getStandardProducer(int, int);
  void getStandardConsumerOwner(int);
  void getStandardStaticConsumer(int, int);
  void getStandardDynamicConsumer(int, int);
  void getStaticEnergyPlan(int, int, int);
  void getDynamicEnergyPlan(int, int, int, int, int, int);

public:
  ConfigBuilder(const char *, int, int, int, int, std::string);
  void buildConfig();
  ~ConfigBuilder();
};

}

#endif /* CONFIGBUILDER_H_ */
