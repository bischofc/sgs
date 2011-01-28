
#ifndef LOGGER_H_
#define LOGGER_H_

#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>

class Logger {                                                                  // TODO führt zu Problemen wenn mehrere Instanzen laufen

public:
  enum Loglevel { OFF, FATAL, ERROR, WARN, DEBUG };

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
  void warn(std::string);
  void error(std::string);
  void fatal(std::string);
  static std::string toString(int);
  static std::string toString(double);
  virtual ~Logger();
};

#endif /* LOGGER_H_ */
