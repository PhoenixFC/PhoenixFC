#include "mbed.h"
#include "pc.h"
#include "receiver_config.h"
#include "pwm_receiver.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

Computer console = Computer();

ReceiverConfig rxConfig = ReceiverConfig();
PwmReceiver rx = PwmReceiver(&rxConfig);

void init(void)
{
  console.debug("Starting up PhoenixFC!\n");

  console.debug("Loading config file...");
  rxConfig.load();
  console.debug("done.\n");
}

void loop(void)
{
  if( console.readable() ) {
    console.read();
    console.read();

    // rxPacket = rx.readPacket();
    // console.debug(
    //   "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
    //   rxPacket.throttle, rxPacket.yaw, rxPacket.pitch, rxPacket.roll, 0, 0
    // );

    console.debug(
      "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
      rx.readThrottle(), rx.readYaw(), rx.readPitch(), rx.readRoll(), 0, 0
    );
  }
  wait(0.005);
}

// void read_rx_loop(void)
// {
//   PwmReceiver rx = PwmReceiver();
//
//   while (1) {
//     rxPacket = rx.readPacket();
//     Thread::wait(50);
//   }
// }

void printChannelConfig(ChannelConfig config)
{
  console.debug("Min Value: %4lu ", config.minValue);
  console.debug("Max Value: %4lu ", config.maxValue);
  console.debug("Reverse: %d ", config.reverse);
  console.debug("Channel: %lu\n", config.channel);
}

void printChannelConfigs()
{
  console.debug("Throttle Config: ");
  printChannelConfig(rxConfig.throttleConfig());
  console.debug("Yaw Config: ");
  printChannelConfig(rxConfig.yawConfig());
  console.debug("Pitch Config: ");
  printChannelConfig(rxConfig.pitchConfig());
  console.debug("Roll Config: ");
  printChannelConfig(rxConfig.rollConfig());
}

int main()
{
    init();

    // Thread thread(read_rx_loop);

    while (1) {
        loop();
        // read_rx_loop();
        // printChannelConfigs();

        // wait();
    }
}
