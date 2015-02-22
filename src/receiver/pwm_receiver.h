#include "mbed.h"
#include "PwmIn.h"
#include "channel_config.h"
#include "receiver_config.h"

class PwmReceiver {
public:
  PwmReceiver(ReceiverConfig *aConfig);

  int readThrottle();
  int readYaw();
  int readPitch();
  int readRoll();

  int readChannel(int number);

protected:
  int readChannelWithConfig(ChannelConfig config);
  PwmIn& getChannel(int number);

private:

  ReceiverConfig *config;
  PwmIn channels[4];

};
