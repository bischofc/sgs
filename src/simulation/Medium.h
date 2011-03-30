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

#ifndef simulation_medium_medium_h
#define simulation_medium_medium_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include "exceptions/EnergyException.h"
#include "consumers/ConsumerOwner.h"
#include "producers/ProducerOwner.h"


namespace simulation {
namespace medium {

class Medium : public Parsable {
  std::string name;
  std::vector<int> loadAdjustment;
  std::vector< boost::shared_ptr<endpoint::consumer::ConsumerOwner> > consumerOwnerList;
  boost::shared_ptr<endpoint::producer::ProducerOwner> producerOwner;
  int wattage;
  bool producerOwnerSet;

 public:
  Medium(std::string);
  void registerConsumerOwner(boost::shared_ptr<endpoint::consumer::ConsumerOwner>);
  void registerProducerOwner(boost::shared_ptr<endpoint::producer::ProducerOwner>);
  void oneStep() throw (exception::EnergyException);
  int getNumberOfConsumers();
  int getCurrentWattage();
  virtual ~Medium() {}
};

}} /* end of namespaces */

#endif
