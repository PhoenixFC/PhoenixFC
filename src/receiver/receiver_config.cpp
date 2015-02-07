#include "receiver_config.h"

LocalFileSystem local("local");

ReceiverConfig::ReceiverConfig() :
  _throttleConfig(ChannelConfig()),
  _yawConfig(ChannelConfig()),
  _pitchConfig(ChannelConfig()),
  _rollConfig(ChannelConfig())
{

}

bool ReceiverConfig::load()
{
  ConfigFile configFile;

  if (configFile.read("/local/config.cfg"))
  {
    // File exists, read the config values for each channel
    loadChannelConfig("THR", &configFile, &_throttleConfig);
    loadChannelConfig("YAW", &configFile, &_yawConfig);
    loadChannelConfig("PIT", &configFile, &_pitchConfig);
    loadChannelConfig("ROL", &configFile, &_rollConfig);
  }
  else
  {
    // File does not exist, init with default values
    // TODO:
  }
}

bool ReceiverConfig::loadChannelConfig(char const *prefix, ConfigFile *configFile, ChannelConfig *channelConfig)
{
  channelConfig->minValue = getInt(prefix, "min", configFile);
  channelConfig->maxValue = getInt(prefix, "max", configFile);
  channelConfig->channel = getInt(prefix, "cha", configFile);
  channelConfig->reverse = getBool(prefix, "rev", configFile);
  return true;
}

// TODO: move this to the ConfigFile class
int ReceiverConfig::getInt(char const *prefix, char const *suffix, ConfigFile *configFile)
{
  char value[BUFSIZ];
  char key[8];

  snprintf(key, sizeof(key), "%s.%s", prefix, suffix);
  if (configFile->getValue(key, &value[0], sizeof(value)))
  {
    return atoi(value);
  }
  else
  {
    return 0;
  }
}

// TODO: move this to the ConfigFile class
bool ReceiverConfig::getBool(char const *prefix, char const *suffix, ConfigFile *configFile)
{
  char value[BUFSIZ];
  char key[8];
  snprintf(key, sizeof(key), "%s.%s", prefix, suffix);

  if (configFile->getValue(key, &value[0], sizeof(value)))
  {
    return strcmp(value,"true") == 0 ? true : false;
  }
  else
  {
    return false;
  }
}

bool ReceiverConfig::save()
{
  // TODO: implement a save function
  return false;
}

ChannelConfig ReceiverConfig::throttleConfig()
{
  return _throttleConfig;
}

ChannelConfig ReceiverConfig::yawConfig()
{
  return _yawConfig;
}

ChannelConfig ReceiverConfig::pitchConfig()
{
  return _pitchConfig;
}

ChannelConfig ReceiverConfig::rollConfig()
{
  return _rollConfig;
}
