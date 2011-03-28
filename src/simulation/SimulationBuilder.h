/*
Copyright (C) 2010 Christian Bischof (bischof.christian@gmail.com)
This file is part of "Smart Grid Simulator".

"Smart Grid Simulator" is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Smart Grid Simulator" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Smart Grid Simulator".  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef simulation_config_simulationBuilder_h
#define simulation_config_simulationBuilder_h

#include "tinyxml.h"
#include "xpath_static.h"
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

    endpointType(std::string t) {
      type = t;
    }
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
