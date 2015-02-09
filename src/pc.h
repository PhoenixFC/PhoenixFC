#include "mbed.h"

#ifndef COMPUTER
#define COMPUTER

class Computer {

public:
  Computer();

  void debug(const char* msg);
  void debug(const char* format, int value);
  void debug(const char* format, int value1, int value2, int value3, int value4);
  void debug(const char* format, int value1, int value2, int value3, int value4, int value5, int value6);

  void debug(const char* format, char *value);

  char read();
  bool readable();

private:
  Serial serial;

};

// extern Computer console;

#endif
