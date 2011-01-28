
#include "Logger.h"
#include "Simulation.h"

std::vector< boost::shared_ptr<Logger> > Logger::loggerInstances;

Logger::Logger(std::string fileName, Loglevel l) {
  _level = l;
  _fileName = fileName;
  _firstOpen = true;
  if(l != OFF) openFile();
}

Logger::~Logger() {
  closeFile();
}

/*
 * @l only has an effect when first instance of @fileName is created
 * to change level afterwards use setLoglevel()
 */
boost::shared_ptr<Logger> Logger::getInstance(std::string fileName, Loglevel l) {
  if(!loggerInstances.empty()) {
    for(std::vector< boost::shared_ptr<Logger> >::iterator it = loggerInstances.begin(); it < loggerInstances.end(); it++) {
      std::string tmp = (*it)->_fileName;
      if(fileName.compare(tmp)) return *it;                                     //TODO geht nicht :(
    }
  }
  boost::shared_ptr<Logger> newLogger (new Logger(fileName, l));
  loggerInstances.push_back(newLogger);
  return newLogger;
}

void Logger::changeLoglevel(Loglevel l) {
  if(_level == l) return;
  _level = l;
  if(l == OFF) _file.close();
  else {
    openFile();
  }
}

void Logger::openFile() {
  if(!_file.is_open()) {
    std::ios_base::openmode mode;
    if(_firstOpen) {
      _firstOpen = false;
       mode =  std::fstream::out;
      _file.open(_fileName.c_str(), mode);
      _file << std::endl << std::endl;
      _file << "###################################" << std::endl;
      _file << "# Log from " << 0 << " with level " << _level << std::endl;
      _file << "###################################" << std::endl;
      _file << std::endl;
    } else {
      mode = std::fstream::out|std::fstream::app;
      _file.open(_fileName.c_str(), mode);
    }
  }
}

void Logger::closeFile() {
  if(_file.is_open()) _file.close();
}

void Logger::debug(std::string log) {
  if(_level == DEBUG) writeToFile("DEBUG: " + log);
}

void Logger::warn(std::string log) {
  if(_level >= WARN) writeToFile("WARNING: " + log);
}

void Logger::error(std::string log) {
  if(_level >= ERROR) writeToFile("ERROR: " + log);
}

void Logger::fatal(std::string log) {
  if(_level >= FATAL) writeToFile("FATAL: " + log);
}

void Logger::writeToFile(std::string log) {
  if(!_file.is_open()) return;
  _file << simulation::Simulation::getTime() << ": " << log << std::endl;
//  _file << log << std::endl;
  _file.flush();
}

std::string Logger::toString(int tmp) {
  stringstream ss;
  std::string retVal;
  ss << tmp;
  ss >> retVal;
  return retVal;
}

std::string Logger::toString(double tmp) {
  stringstream ss;
  std::string retVal;
  ss << tmp;
  ss >> retVal;
  return retVal;
}
