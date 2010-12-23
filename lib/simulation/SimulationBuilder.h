#ifndef simulation_config_simulationBuilder_h
#define simulation_config_simulationBuilder_h

#include <map>

#include "tinyxml.h"
#include "ParserException.h"
#include "Medium.h"
#include "ConsumerOwner.h"
#include "ProducerOwner.h"
#include "DeviceFactory.h"

using namespace std;

namespace simulation {
namespace config {

class SimulationBuilder {

  struct classDesc {
    std::string classType;
    void * classPtr;
    std::map<string, string> attributes;
  };

public:
  static medium::Medium * buildSimulation( const char *, map<string, string> & ) throw (exception::ParserException);
private:
  static classDesc parse( tinyxml::TiXmlNode *, int ) throw (exception::ParserException);
  static map<string, string> parseAttributes( tinyxml::TiXmlElement * );
  static string makeIndent( int );

};

} /* End of namespace simulation.config */
} /* End of namespace simulation */

#endif // simulation_config_simulationBuilder_h
