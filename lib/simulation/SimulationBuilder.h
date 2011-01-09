#ifndef simulation_config_simulationBuilder_h
#define simulation_config_simulationBuilder_h

#include <map>

#include "tinyxml.h"
#include "exceptions/ParserException.h"
#include "Medium.h"
#include "consumers/ConsumerOwner.h"
#include "producers/ProducerOwner.h"
#include "DeviceFactory.h"

using namespace std;

namespace simulation {
namespace config {

class SimulationBuilder {

  struct classDesc {
    std::string classType;
    boost::shared_ptr<Parsable> classPtr;
    std::map<string, string> attributes;
  };

public:
  static map<string, string> buildConfiguration( const char * ) throw (exception::ParserException);
  static boost::shared_ptr<medium::Medium> buildSimulation( const char * ) throw (exception::ParserException);
private:
  static classDesc parse( tinyxml::TiXmlNode *, int ) throw (exception::ParserException);
  static map<string, string> parseAttributes( tinyxml::TiXmlElement * );
  static string makeIndent( int );

};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif // simulation_config_simulationBuilder_h
