#include "SimulationBuilder.h"

//TODO
#include <iostream>

namespace simulation {
namespace config {

vector< boost::shared_ptr<SimulationBuilder::endpointType> > SimulationBuilder::endpointTypes;

boost::shared_ptr<medium::Medium> SimulationBuilder::buildSimulation( const char * fileName ) throw (exception::ParserException) {
  TiXmlDocument doc (fileName);
  bool loaded = doc.LoadFile();

  if(loaded) {
    // setup the "paths"
    TiXmlElement * rootElt = doc.FirstChildElement();
    TiXmlElement * typesElt = rootElt->FirstChildElement();
    TiXmlElement * mediumElt = rootElt->FirstChildElement()->NextSiblingElement();

    std::string m_id = TinyXPath::XAp_xpath_attribute(mediumElt, "@m-id")->Value();
    boost::shared_ptr<medium::Medium> medium (new medium::Medium(m_id));

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

} /* End of namespace simulation.config */
} /* End of namespace simulation */
