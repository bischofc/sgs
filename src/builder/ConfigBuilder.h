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
  void openFile(const char *);
  void buildHull();
  void getConfig();
  void getStandardMedium();
  void getProducer( std::string type, int id );
  void getConsumer( std::string type, int id );

  // to adapt
  void getEndpointTypes();
  void getProducerOwner( int id);
  void getConsumerOwner( int id);

public:
  ConfigBuilder( const char* fileName, int duration, int resolution, int consumerNo, std::string mediumName = "cable");
  void buildConfig();
  virtual ~ConfigBuilder();
};

}

#endif /* builder_configBuilder_h */
