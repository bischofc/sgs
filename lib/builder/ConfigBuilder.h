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

  // basics
  // ------
  void buildHull();
  void getConfigTag();
  void getStandardMedium();
  void getStandardProducerOwner( int id);
  void getStandardConsumerOwner( int id);
  void getStaticEnergyPlan( int start, int end, int rate);
  void getDynamicEnergyPlan( int start, int end, int period, int highTime, int min, int max);

  // fun stuff
  // ---------
  void getWindmill( int id, int subid);
  void getStandardStaticConsumer( int id, int subid);
  void getStandardDynamicConsumer( int id, int subid);

public:
  ConfigBuilder( const char* fileName, int duration, int consumerNo, std::string mediumName = "cable");
  void buildConfig();
  ~ConfigBuilder();
};

}

#endif /* CONFIGBUILDER_H_ */
