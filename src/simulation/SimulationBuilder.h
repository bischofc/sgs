#ifndef simulation_config_simulationBuilder_h
#define simulation_config_simulationBuilder_h

#include "tinyxml.h"
#include "xpath_static.h" // TODO später einbauen
#include "exceptions/ParserException.h"
#include "Medium.h"
#include "consumers/ConsumerOwner.h"
#include "producers/ProducerOwner.h"
#include "DeviceFactory.h"

namespace simulation {
namespace config {

class SimulationBuilder {

  struct endpointType {
    std::string type;
    std::vector< std::pair<std::string, std::string> > devices;
  };

private:
  static std::vector< boost::shared_ptr<endpointType> > endpointTypes;

private:
  SimulationBuilder();
  static bool toSkip(std::string ownerType, std::string deviceType);
  static boost::shared_ptr<endpoint::producer::ProducerOwner> getProducerOwner(TiXmlElement * typeDefElement, std::string id, std::string type);
  static boost::shared_ptr<endpoint::consumer::ConsumerOwner> getConsumerOwner(TiXmlElement * typeDefElement, std::string id, std::string type);
  static boost::shared_ptr<endpointType> getEndpointDescription(TiXmlElement * typeDefElement, std::string type);

public:
  static boost::shared_ptr<medium::Medium> buildSimulation( const char *, int &, int & ) throw (exception::ParserException);
  virtual ~SimulationBuilder() {}

};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif // simulation_config_simulationBuilder_h
