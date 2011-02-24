#include "SimulationBuilder.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

std::vector< boost::shared_ptr<SimulationBuilder::endpointType> > SimulationBuilder::endpointTypes;

boost::shared_ptr<medium::Medium> SimulationBuilder::buildSimulation( const char * fileName, int & duration, int & resolution ) throw (exception::ParserException) {
  TiXmlDocument doc (fileName);
  bool loaded = doc.LoadFile();

  if(loaded) {
    std::stringstream ss;

    // setup the "paths"
    TiXmlElement * rootElt = doc.FirstChildElement();
    TiXmlElement * configElt = TinyXPath::XNp_xpath_node(rootElt, "/simulation/config/simDesc")->ToElement();
    TiXmlElement * typesElt = TinyXPath::XNp_xpath_node(rootElt, "/simulation/endpoint-types")->ToElement();
    TiXmlElement * mediumElt = TinyXPath::XNp_xpath_node(rootElt, "/simulation/medium")->ToElement();

    // read duration and resolution
    ss << TinyXPath::XAp_xpath_attribute(configElt, "@duration")->Value(); ss >> duration; ss.clear();
    ss << TinyXPath::XAp_xpath_attribute(configElt, "@resolution")->Value(); ss >> resolution; ss.clear();

    // build medium
    std::string m_id = TinyXPath::XAp_xpath_attribute(mediumElt, "@m-id")->Value();
    boost::shared_ptr<medium::Medium> medium (new medium::Medium(m_id));

    // add medium endpoints
    for(TiXmlElement * node = mediumElt->FirstChildElement(); node; node = node->NextSiblingElement()) {
      std::string oId = TinyXPath::XAp_xpath_attribute(node, "@o-id")->Value();
      std::string endpointType = TinyXPath::XAp_xpath_attribute(node, "@type")->Value();
      std::string ownerType = node->Value();

      if(ownerType == "producerOwner") {
        medium->registerEndpoint(getProducerOwner(typesElt, oId, endpointType));
      } else if(ownerType == "consumerOwner") {
        medium->registerEndpoint(getConsumerOwner(typesElt, oId, endpointType));
      } else {
        throw exception::ParserException("Endpoint type not recognized.");
      }
    }

    return medium;
  } else throw exception::ParserException("Configuration file could not be loaded");
}

boost::shared_ptr<endpoint::producer::ProducerOwner> SimulationBuilder::getProducerOwner(TiXmlElement * typeDefElement, std::string id, std::string type) {
  boost::shared_ptr<endpointType> eDesc = getEndpointDescription(typeDefElement, type);

  boost::shared_ptr<endpoint::producer::ProducerOwner> producerOwner (new endpoint::producer::ProducerOwner(id));
  for(std::vector< std::pair<std::string, std::string> >::iterator it = eDesc->devices.begin();
                  it != eDesc->devices.end(); it++) {
    std::string pId = id+"-"+it->first;
    std::string pType = it->second;
    boost::shared_ptr<endpoint::producer::Producer> producer = endpoint::DeviceFactory::getProducerInstance(pType, pId, true);
    producerOwner->addProducer(producer);
  }
  return producerOwner;
}

boost::shared_ptr<endpoint::consumer::ConsumerOwner> SimulationBuilder::getConsumerOwner(TiXmlElement * typeDefElement, std::string id, std::string type) {
  boost::shared_ptr<endpointType> eDesc = getEndpointDescription(typeDefElement, type);

  boost::shared_ptr<endpoint::consumer::ConsumerOwner> consumerOwner (new endpoint::consumer::ConsumerOwner(id));
  for(std::vector< std::pair<std::string, std::string> >::iterator it = eDesc->devices.begin();
                  it != eDesc->devices.end(); it++) {
    std::string cId = id+"-"+it->first;
    std::string cType = it->second;

    // some devices are not available for some part of the consumer type (e.g. not all retirees have computers...)
    if(toSkip(type, cType)) continue;

    boost::shared_ptr<endpoint::consumer::Consumer> consumer = endpoint::DeviceFactory::getConsumerInstance(cType, cId);
    consumerOwner->addConsumer(consumer);
  }
  return consumerOwner;
}

boost::shared_ptr<SimulationBuilder::endpointType> SimulationBuilder::getEndpointDescription(TiXmlElement * typeDefElement, std::string eType) {
  // if in list return
  for(std::vector< boost::shared_ptr<endpointType> >::iterator it = endpointTypes.begin(); it!=endpointTypes.end(); it++) {
    if((*it)->type == eType) return *it;
  }

  // else create and attach to list
  std::string search = "//endpoint-types/type[@id='"+eType+"']";
  TiXmlNode * target = TinyXPath::XNp_xpath_node(typeDefElement, search.c_str());
  boost::shared_ptr<endpointType> tmp (new endpointType);                       // TODO konstruktor erstellen. wie?
  tmp->type = eType;

  for(TiXmlElement * ep = target->FirstChildElement(); ep; ep = ep->NextSiblingElement()) {
    std::string dId = TinyXPath::XAp_xpath_attribute(ep, "@d-id")->Value();
    std::string dType = TinyXPath::XAp_xpath_attribute(ep, "@type")->Value();
    std::pair<std::string, std::string> pair (dId, dType);
    tmp->devices.push_back(pair);
  }

  endpointTypes.push_back(tmp);
  return tmp;
}

bool SimulationBuilder::toSkip(std::string ownerType, std::string deviceType) {
  // first check for heater and boiler because it is the same for every group
  if((deviceType == "heaterLow" || deviceType == "heaterHigh") && helper::RandomNumbers::getRandom() > 0.25) return true;
  if((deviceType == "boilerLow" || deviceType == "boilerMid" || deviceType == "boilerHigh") && helper::RandomNumbers::getRandom() > 0.33) return true;

  // if fam4- or fam5-consumer there is nothing else to check, so return
  if(ownerType == "fam4-consumer" || ownerType == "fam5-consumer") return false;

  // check the rest of the consumer types
  if(ownerType == "fam2-consumer") {
    if(deviceType == "freezer" && helper::RandomNumbers::getRandom() > 0.9) return true;
    if(deviceType == "dishwasherMid" && helper::RandomNumbers::getRandom() > 0.5) return true;
    if(deviceType == "oven" && helper::RandomNumbers::getRandom() > 0.5) return true;
    if(deviceType == "computerLow" && helper::RandomNumbers::getRandom() > 0.9) return true;
  } else if(ownerType == "shift-consumer") {
    if(deviceType == "dishwasherMid" && helper::RandomNumbers::getRandom() > 0.85) return true;
    if(deviceType == "oven" && helper::RandomNumbers::getRandom() > 0.85) return true;
    if(deviceType == "computerHigh" && helper::RandomNumbers::getRandom() > 0.9) return true;
  } else if(ownerType == "retiree-consumer") {
    if(deviceType == "appliances" && helper::RandomNumbers::getRandom() > 0.5) return true;
    if(deviceType == "oven" && helper::RandomNumbers::getRandom() > 0.5) return true;
    if(deviceType == "coffeemachineLow" && helper::RandomNumbers::getRandom() > 0.75) return true;
    if(deviceType == "microwaveLow" && helper::RandomNumbers::getRandom() > 0.25) return true;
    if(deviceType == "kettleLow" && helper::RandomNumbers::getRandom() > 0.7) return true;
    if(deviceType == "tumblerLow" && helper::RandomNumbers::getRandom() > 0.75) return true;
    if(deviceType == "computerLow" && helper::RandomNumbers::getRandom() > 0.2) return true;
  }
  return false;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
