#include "SimulationBuilder.h"

namespace simulation {
namespace config {

std::map<string, string> SimulationBuilder::buildConfiguration( const char * fileName ) throw (exception::ParserException) {
  tinyxml::TiXmlDocument doc;
  map<string, string> attributes;

  bool loaded = doc.LoadFile(fileName);
  if(loaded) {
    // auf config zeigen und auslesen
    tinyxml::TiXmlNode * node = doc.FirstChildElement()->FirstChildElement();
    attributes = parseAttributes(node->FirstChildElement()->ToElement()); //todo clean up; quick'n'dirty to get the values
    return attributes;
  } else throw exception::ParserException("Opening or parsing of configuration file (xml) failed");
}

medium::Medium * SimulationBuilder::buildSimulation( const char * fileName ) throw (exception::ParserException) {
  medium::Medium * medium;
  tinyxml::TiXmlDocument doc;
  bool loaded = doc.LoadFile(fileName);

  if(loaded) {
    // auf medium zeigen und erstellen
    tinyxml::TiXmlNode * node = doc.FirstChildElement()->FirstChildElement()->NextSibling();
    classDesc cd = parse(node,1);
    if(cd.classType == "medium") {
      medium = (medium::Medium *) cd.classPtr;
    } else throw exception::ParserException("Parsing of simulation descripton (xml) failed: 'medium' is not where it should be");
  } else throw exception::ParserException("Opening or parsing of configuration file (xml) failed");

  return medium;
}

SimulationBuilder::classDesc SimulationBuilder::parse( tinyxml::TiXmlNode * parent, int i ) throw (exception::ParserException) {
  // return if null pointer
  if( !parent ) {
    classDesc cd;
    return cd;
  }

  // do parsing
  classDesc parentClassDesc;
  int type = parent->Type();
  switch (type) {
    /* not used so far
    case TiXmlNode::TINYXML_DOCUMENT:
      cout << makeIndent(i) << "* Document" << endl;
      break;
    case TiXmlNode::TINYXML_COMMENT:
      cout << makeIndent(i) << "L Comment: " << parent->Value() << endl;
      break;
    case TiXmlNode::TINYXML_TEXT:
      cout << makeIndent(i) << "L Text: " << parent->Value() << endl;
      break;
    case TiXmlNode::TINYXML_DECLARATION:
      cout << makeIndent(i) << "L Declaration" << endl;
      break;
    */
    case tinyxml::TiXmlNode::TINYXML_ELEMENT:
      parentClassDesc.classType = parent->Value();
      parentClassDesc.attributes = parseAttributes(parent->ToElement());
      break;
    default:
      classDesc cd;
      return cd;
  }

  // parse children
  vector< classDesc > tmpStore;
  for(tinyxml::TiXmlNode * child = parent->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {
    classDesc  cd = parse(child, i+1);
    tmpStore.push_back(cd);
  }

  // create elementType and connect children to parent
  // return retVal, otherwise throw exception
  vector< classDesc >::iterator storeIterator;
  if(parentClassDesc.classType == "medium") {
    //create elementType
    map<string, string>::iterator it = parentClassDesc.attributes.find("name");
    medium::Medium * medium = new medium::Medium (it->second);
    parentClassDesc.classPtr = medium;

    // connect children to parent
    for(storeIterator = tmpStore.begin(); storeIterator != tmpStore.end(); storeIterator++) {
      endpoint::MediumEndpoint * ep;
      if(storeIterator->classType == "producerOwner") {
        ep = (endpoint::producer::ProducerOwner *) storeIterator->classPtr;
      } else if(storeIterator->classType == "consumerOwner") {
        ep = (endpoint::consumer::ConsumerOwner *) storeIterator->classPtr;
      } else {
        throw exception::ParserException("Medium endpoint type not implemented: please check simulation description (xml)");
      }
      medium->registerEndpoint(ep);
    }

    return parentClassDesc;
  }
  else if(parentClassDesc.classType == "producerOwner") {
    // create elementType
    map<string, string>::iterator it = parentClassDesc.attributes.find("id");
    endpoint::producer::ProducerOwner * producerOwner = new endpoint::producer::ProducerOwner (it->second);
    parentClassDesc.classPtr = producerOwner;

    // connect children to parent
    for(storeIterator = tmpStore.begin(); storeIterator != tmpStore.end(); storeIterator++) {
      endpoint::producer::Producer * p = (endpoint::producer::Producer *) storeIterator->classPtr;
      producerOwner->addProducer(p);
    }

    return parentClassDesc;
  }
  else if(parentClassDesc.classType == "consumerOwner") {
    // create elementType
    map<string, string>::iterator it = parentClassDesc.attributes.find("id");
    endpoint::consumer::ConsumerOwner * consumerOwner = new endpoint::consumer::ConsumerOwner (it->second);
    parentClassDesc.classPtr = consumerOwner;

    // connect children to parent
    for(storeIterator = tmpStore.begin(); storeIterator != tmpStore.end(); storeIterator++) {
      endpoint::consumer::Consumer * c = (endpoint::consumer::Consumer *) storeIterator->classPtr;
      consumerOwner->addConsumer(c);
    }
    return parentClassDesc;
  }
  else if(parentClassDesc.classType == "producer") {
    map<string, string>::iterator it;
    it = parentClassDesc.attributes.find("id"); std::string id = it->second;
    it = parentClassDesc.attributes.find("type"); std::string type = it->second;
    parentClassDesc.classPtr = endpoint::DeviceFactory::getProducerInstance(type, id, true);
    return parentClassDesc;
  }
  else if(parentClassDesc.classType == "consumer") {
    map<string, string>::iterator it;
    it = parentClassDesc.attributes.find("id"); std::string id = it->second;
    it = parentClassDesc.attributes.find("type"); std::string type = it->second;
    parentClassDesc.classPtr = endpoint::DeviceFactory::getConsumerInstance(type, id);
    return parentClassDesc;
  }
  else {
    throw exception::ParserException("XML element type not recognized. Check simulation description (xml) for errors.");
  }
}

map<string, string> SimulationBuilder::parseAttributes( tinyxml::TiXmlElement * elt ) {
  map<string, string> ret;
  if(!elt) return ret;

  for(tinyxml::TiXmlAttribute * attr = elt->FirstAttribute(); attr != 0; attr = attr->Next()) {
    pair <string, string> pair (attr->Name(), attr->Value());
    ret.insert(pair);
  }
  return ret;
}

std::string SimulationBuilder::makeIndent( int i ) {
  std::string str = "";
  for (int j=0; j<i; j++) {
    str += "  ";
  }
  return str;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
