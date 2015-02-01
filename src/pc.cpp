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

Computer console = Computer();
