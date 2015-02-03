#include "mbed.h"

class Computer {

public:
  Computer();

  void debug(const char* msg);
  void debug(const char* format, int value);
  void debug(const char* format, int value1, int value2, int value3, int value4);

private:
  Serial serial;

};

extern Computer console;
