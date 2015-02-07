#include "pwm_receiver.h"
#include "PwmIn.h"

#define CHANNEL_SCALE 1000000

PwmReceiver::PwmReceiver(ReceiverConfig *aConfig) :
  config(aConfig),
  channels({PwmIn(p21), PwmIn(p22), PwmIn(p23), PwmIn(p24), PwmIn(p25), PwmIn(p26)})
{
  
}

// RxPacket PwmReceiver::readPacket()
// {
//   RxPacket newPacket();
//   newPacket.throttle = readThrottle();
//   newPacket.yaw = readYaw();
//   newPacket.pitch = readPitch();
//   newPacket.roll = readRoll();
//   return newPacket;
// }

int PwmReceiver::readChannel(ChannelConfig config)
{
  PwmIn& channel = getChannel(config.channel);
  int rawValue = (int)(channel.pulsewidth() * CHANNEL_SCALE);
  if( rawValue <= config.minValue ) {
    return config.reverse ? 1000 : 0;
  }
  else if( rawValue >= config.maxValue ) {
    return config.reverse ? 0 : 1000;
  } else {
    float scale = (float)(config.maxValue - config.minValue) / 1000;
    int scaledValue = (int)((rawValue - config.minValue) / scale);
    return config.reverse ? (scaledValue - 1000) * -1 : scaledValue;
  }
}

int PwmReceiver::readThrottle()
{
  return readChannel(config->throttleConfig());
}

int PwmReceiver::readYaw()
{
  return readChannel(config->yawConfig());
}

int PwmReceiver::readPitch()
{
  return readChannel(config->pitchConfig());
}

int PwmReceiver::readRoll()
{
  return readChannel(config->rollConfig());
}

PwmIn& PwmReceiver::getChannel(int number)
{
  return channels[number-1];
}
