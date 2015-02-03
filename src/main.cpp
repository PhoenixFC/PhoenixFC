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

  console.debug("Throttle:%4lu,Yaw:%4lu,Pitch:%4lu,Roll:%4lu;", rx.readThrottle(), rx.readYaw(), rx.readPitch(), rx.readroll());

  wait(0.1);
}

int main()
{
    init();

    while (1) {
        loop();
    }
}
