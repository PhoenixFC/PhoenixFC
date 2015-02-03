#include "pc.h"
#include "mbed.h"

Computer::Computer() : serial(Serial(USBTX, USBRX))
{
}

void Computer::debug(const char* msg)
{
  serial.printf(msg);
}

void Computer::debug(const char* format, int value)
{
  serial.printf(format, value);
}

void Computer::debug(const char* format, int value1, int value2, int value3, int value4)
{
  serial.printf(format, value1, value2, value3, value4);
}

Computer console = Computer();
