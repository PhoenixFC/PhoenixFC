#include "mbed.h"

class Computer {

public:
  Computer();

  void debug(const char* msg);
  void debug(const char* format, int value);

private:
  Serial serial;

};

extern Computer console;
