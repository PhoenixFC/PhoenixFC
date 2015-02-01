#include "pwm_receiver.h"
#include "PwmIn.h"
#include "pc.h"

#define CHANNEL_SCALE 1000000

PwmReceiver::PwmReceiver() :
  throttle(PwmIn(p21)), yaw(PwmIn(p6)), pitch(PwmIn(p7)), role(PwmIn(p8)),
  throttleConfig(ChannelConfig()), yawConfig(ChannelConfig()), pitchConfig(ChannelConfig()), roleConfig(ChannelConfig())
{
  // TODO: Load config from a config file written from the PhoenixFC app.
  throttleConfig.minValue = 1120;
  throttleConfig.maxValue = 1943;
}

int PwmReceiver::readChannel(PwmIn& channel, ChannelConfig config)
{
  int rawValue = (int)(channel.pulsewidth() * CHANNEL_SCALE);
  if( rawValue <= config.minValue ) {
    return 0;
  }
  else if( rawValue >= config.maxValue ) {
    return 1000;
  } else {
    float scale = (float)(config.maxValue - config.minValue) / 1000;
    return (int)((rawValue - config.minValue) / scale);
  }
}

int PwmReceiver::readThrottle()
{
  return readChannel(throttle, throttleConfig);
}

int PwmReceiver::readYaw()
{
  return readChannel(yaw, yawConfig);
}

int PwmReceiver::readPitch()
{
  return readChannel(pitch, pitchConfig);
}

int PwmReceiver::readRole()
{
  return readChannel(role, roleConfig);
}
