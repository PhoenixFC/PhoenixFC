#include "pwm_receiver.h"
#include "PwmIn.h"
#include "pc.h"

#define CHANNEL_SCALE 1000000

PwmReceiver::PwmReceiver() :
  throttle(PwmIn(p21)), yaw(PwmIn(p22)), pitch(PwmIn(p23)), roll(PwmIn(p24)),
  throttleConfig(ChannelConfig()), yawConfig(ChannelConfig()), pitchConfig(ChannelConfig()), rollConfig(ChannelConfig())
{
  // TODO: Load config from a config file written from the PhoenixFC app.
  throttleConfig.minValue = 1120;
  throttleConfig.maxValue = 1943;

  yawConfig.minValue = 1120;
  yawConfig.maxValue = 1933;
  yawConfig.reverse = true;

  pitchConfig.minValue = 1122;
  pitchConfig.maxValue = 1927;

  rollConfig.minValue = 1125;
  rollConfig.maxValue = 1933;
  rollConfig.reverse = true;

}

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

int PwmReceiver::readroll()
{
  return readChannel(roll, rollConfig);
}
