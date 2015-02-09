#include "mbed.h"
#include "pc.h"
#include "receiver_config.h"
#include "pwm_receiver.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

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

    led1 = !led1;

    char char1 = console.read();
    char char2 = console.read();

    if( char1 == 'R' )
    {
      if( char2 == 'X' )
      {
        console.debug(
          "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
          rx.readThrottle(), rx.readYaw(), rx.readPitch(), rx.readRoll(), 0, 0
        );
      }
      else
      {
        console.debug(
          "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
          rx.readChannel(1), rx.readChannel(2), rx.readChannel(3), rx.readChannel(4), rx.readChannel(5), rx.readChannel(6)
        );
      }
    }


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
