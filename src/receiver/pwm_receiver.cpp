#include "pwm_receiver.h"
#include "PwmIn.h"

#define CHANNEL_SCALE 1000000

PwmReceiver::PwmReceiver(ReceiverConfig *aConfig) :
  config(aConfig),
  channels({PwmIn(p5), PwmIn(p6), PwmIn(p7), PwmIn(p8)})
{

}

int PwmReceiver::readChannel(int number)
{
  PwmIn& channel = getChannel(number);
  return (int)(channel.pulsewidth() * CHANNEL_SCALE);
}

int PwmReceiver::readChannelWithConfig(ChannelConfig config)
{
  int rawValue = readChannel(config.channel);
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
  return readChannelWithConfig(config->throttleConfig());
}

int PwmReceiver::readYaw()
{
  return readChannelWithConfig(config->yawConfig());
}

int PwmReceiver::readPitch()
{
  return readChannelWithConfig(config->pitchConfig());
}

int PwmReceiver::readRoll()
{
  return readChannelWithConfig(config->rollConfig());
}

PwmIn& PwmReceiver::getChannel(int number)
{
  return channels[number-1];
}
