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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>

class Logger {                                                                  // TODO führt zu Problemen wenn mehrere Instanzen laufen

public:
  enum Loglevel { OFF, FATAL, ERROR, WARN, INFO, DEBUG, CUSTOM };

private:
  static std::vector< boost::shared_ptr<Logger> > loggerInstances;
  std::string _fileName;
  Loglevel _level;
  bool _firstOpen;
  std::ofstream _file;

private:
  Logger(std::string fileName, Loglevel l);
  void writeToFile(std::string);
  void openFile();
  void closeFile();

public:
  static boost::shared_ptr<Logger> getInstance(std::string fileName, Loglevel l=OFF);
  void changeLoglevel(Loglevel l);
  void debug(std::string);
  void info(std::string);
  void warn(std::string);
  void error(std::string);
  void fatal(std::string);
  void rawToFile(std::string rawLog);
  static std::string toString(int);
  static std::string toString(double);
  virtual ~Logger();
};

#endif /* LOGGER_H_ */
