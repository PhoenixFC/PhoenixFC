#include "mbed.h"
#include "PwmIn.h"
#include "channel_config.h"
#include "receiver_config.h"

// struct RxPacket {
//   int throttle = 0;
//   int yaw = 0;
//   int pitch = 0;
//   int roll = 0;
//   int ch5 = 0;
//   int ch6 = 0;
// };

class PwmReceiver {
public:
  PwmReceiver(ReceiverConfig *aConfig);

  int readThrottle();
  int readYaw();
  int readPitch();
  int readRoll();

  int readChannel(int number);

  // RxPacket readPacket();

protected:
  int readChannelWithConfig(ChannelConfig config);
  PwmIn& getChannel(int number);

private:

  ReceiverConfig *config;
  PwmIn channels[6];

};
