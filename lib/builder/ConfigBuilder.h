#ifndef builder_configBuilder_h
#define builder_configBuilder_h

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
  void getProducer( std::string type, int id, int subid );
  void getConsumer( std::string type, int id, int subid );

public:
  ConfigBuilder( const char* fileName, int duration, int consumerNo, std::string mediumName = "cable");
  void buildConfig();
  ~ConfigBuilder();
};

}

#endif /* builder_configBuilder_h */
