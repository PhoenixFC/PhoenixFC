#include "mbed.h"
#include "PwmIn.h"

struct ChannelConfig {
  int minValue = 1000;
  int maxValue = 2000;
  bool reverse = false;
};

class PwmReceiver {
public:
  PwmReceiver();

  int readThrottle();
  int readYaw();
  int readPitch();
  int readroll();

protected:
  int readChannel(PwmIn& channel, ChannelConfig config);

private:

  PwmIn throttle;
  PwmIn yaw;
  PwmIn pitch;
  PwmIn roll;

  ChannelConfig throttleConfig;
  ChannelConfig yawConfig;
  ChannelConfig pitchConfig;
  ChannelConfig rollConfig;

};
