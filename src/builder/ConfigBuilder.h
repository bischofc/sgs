#ifndef builder_configBuilder_h
#define builder_configBuilder_h

#include <fstream>

namespace builder {

class ConfigBuilder {
  std::ofstream file;
  std::string mediumName;
  int duration;
  int resolution;
  int numberOfProducers;
  int numberOfConsumers;

  // basics
  void buildHull();
  void getConfig();
  void getStandardMedium();
  void getProducer( std::string type, int id );
  void getConsumer( std::string type, int id );

  // to adapt
  void getEndpointTypes();
  void getStandardProducerOwner( int id);
  void getConsumerOwner( int id);

public:
  ConfigBuilder( const char* fileName, int duration, int resolution, int consumerNo, std::string mediumName = "cable");
  void buildConfig();
  virtual ~ConfigBuilder();
};

}

#endif /* builder_configBuilder_h */
