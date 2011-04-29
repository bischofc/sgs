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

#include "Logger.h"
#include "Simulation.h"

std::vector< boost::shared_ptr<Logger> > Logger::loggerInstances;

Logger::Logger(std::string fileName, Loglevel l) {
  _level = l;
  _fileName = fileName;
  openFile();
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
      if(fileName.compare(tmp) == 0) return *it;
    }
  }
  boost::shared_ptr<Logger> newLogger (new Logger(fileName, l));
  loggerInstances.push_back(newLogger);
  return newLogger;
}

void Logger::openFile() {
  if(!_file.is_open()) {
    _file.open(_fileName.c_str(), std::fstream::out);
    _file << std::endl << std::endl;
    _file << "###################################" << std::endl;
    _file << "# Log from " << 0 << " with level " << _level << std::endl;
    _file << "###################################" << std::endl;
    _file << std::endl;
  }
}

void Logger::closeFile() {
  if(_file.is_open()) _file.close();
}

void Logger::debug(std::string log) {
  if(_level == DEBUG) writeToFile("DEBUG: " + log);
}

void Logger::info(std::string log) {
  if(_level >= INFO) writeToFile("INFO: " + log);
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

void Logger::custom(std::string rawLog) {
  if(_level != CUSTOM) return;
  if(!_file.is_open()) return;
  _file << rawLog << std::endl;
  _file.flush();
}

void Logger::writeToFile(std::string log) {
  if(!_file.is_open()) return;
  _file << simulation::Simulation::getTime() << ": " << log << std::endl;
//  _file << log << std::endl;
  _file.flush();
}

std::string Logger::toString(int tmp) {
  std::stringstream ss;
  std::string retVal;
  ss << tmp;
  ss >> retVal;
  return retVal;
}

std::string Logger::toString(unsigned tmp) {
  std::stringstream ss;
  std::string retVal;
  ss << tmp;
  ss >> retVal;
  return retVal;
}

std::string Logger::toString(double tmp) {
  std::stringstream ss;
  std::string retVal;
  ss << tmp;
  ss >> retVal;
  return retVal;
}

std::string Logger::toString(const char * tmp) {
  std::string retVal = tmp;
  return retVal;
}
