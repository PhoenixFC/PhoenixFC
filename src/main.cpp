#include "mbed.h"
#include "pc.h"
#include "pwm_receiver.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

PwmReceiver rx = PwmReceiver();

void init(void)
{
  console.debug("Starting up PhoenixFC!\n");
}

void loop(void)
{
  myled1 = !myled1;

  console.debug("Throttle:%4lu,", rx.readThrottle());
  console.debug("Yaw:%4lu,", rx.readYaw());
  console.debug("Pitch:%4lu,", rx.readPitch());
  console.debug("Role:%4lu", rx.readRole());
  console.debug("\n");

  wait(0.1);
}

int main()
{
    init();

    while (1) {
        loop();
    }
}
