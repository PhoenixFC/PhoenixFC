#include "mbed.h"
#include "ConfigFile.h"
#include "channel_config.h"
#include "pc.h"

#ifndef RECEIVER_CONFIG
#define RECEIVER_CONFIG

class ReceiverConfig {
public:
  ReceiverConfig();

  bool load();
  bool save();

  ChannelConfig throttleConfig();
  ChannelConfig yawConfig();
  ChannelConfig pitchConfig();
  ChannelConfig rollConfig();

protected:
  bool loadChannelConfig(char const *prefix, ConfigFile *configFile, ChannelConfig *channelConfig);

  int getInt(char const *prefix, char const *suffix, ConfigFile *configFile);
  bool getBool(char const *prefix, char const *suffix, ConfigFile *configFile);

private:

  ChannelConfig _throttleConfig;
  ChannelConfig _yawConfig;
  ChannelConfig _pitchConfig;
  ChannelConfig _rollConfig;

};

# endif
