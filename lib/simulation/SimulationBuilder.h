#ifndef simulation_SimulationBuilder_h
#define simulation_SimulationBuilder_h

#include <ParserException.h>
#include <Medium.h>
#include <EnergyDistributionPlanFactory.h>
#include <ConsumerOwner.h>
#include <ProducerOwner.h>
#include <Fridge.h>
#include <Windmill.h>
#include <tinyxml.h>
#include <string>
#include <map>

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

#endif // simulation_SimulationBuilder_h
