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

  // RxPacket readPacket();

protected:
  int readChannel(PwmIn& channel, ChannelConfig config);

private:

  ReceiverConfig *config;

  PwmIn throttle;
  PwmIn yaw;
  PwmIn pitch;
  PwmIn roll;

};
