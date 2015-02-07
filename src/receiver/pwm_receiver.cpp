#include "pwm_receiver.h"
#include "PwmIn.h"

#define CHANNEL_SCALE 1000000

PwmReceiver::PwmReceiver(ReceiverConfig *aConfig) :
  throttle(PwmIn(p21)), yaw(PwmIn(p22)), pitch(PwmIn(p23)), roll(PwmIn(p24)), config(aConfig)
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

int PwmReceiver::readChannel(PwmIn& channel, ChannelConfig config)
{
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
  return readChannel(throttle, config->throttleConfig());
}

int PwmReceiver::readYaw()
{
  return readChannel(yaw, config->yawConfig());
}

int PwmReceiver::readPitch()
{
  return readChannel(pitch, config->pitchConfig());
}

int PwmReceiver::readRoll()
{
  return readChannel(roll, config->rollConfig());
}
