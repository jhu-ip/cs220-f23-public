#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class PlotException : public std::runtime_error {
public:
  PlotException(const std::string &msg);
  PlotException(const PlotException &other);
  ~PlotException();

  // note that the compiler generates the copy constuctor and
  // assignment operator
};

#endif // EXCEPTION_H
