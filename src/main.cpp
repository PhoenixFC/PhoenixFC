#include "mbed.h"
#include "receiver_config.h"
#include "pwm_receiver.h"
#include "rtos.h"
#include "MPU6050.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

Serial console(USBTX,USBRX);

ReceiverConfig rxConfig = ReceiverConfig();
PwmReceiver rx = PwmReceiver(&rxConfig);

PwmOut motor1(p21);
PwmOut motor2(p22);
PwmOut motor3(p23);
PwmOut motor4(p24);

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void init(void)
{
  console.printf("Starting up PhoenixFC!\n");

  console.printf("Initialise motors...");
  motor1.period(0.020); // 50 Hz - 20ms period
  motor2.period(0.020);
  motor3.period(0.020);
  motor4.period(0.020);
  float armedPulse = 0.001; // 0% throttle
  motor1.pulsewidth(armedPulse);
  motor2.pulsewidth(armedPulse);
  motor3.pulsewidth(armedPulse);
  motor4.pulsewidth(armedPulse);
  console.printf("done.\n");
  wait(1.0);

  console.printf("Loading config file...");
  rxConfig.load();
  console.printf("done.\n");

  console.printf("Initializing MPU... \n");
  mpu.initialize();

  console.printf("Test Connection... \n");
  bool mpu6050TestResult = mpu.testConnection();

  if(mpu6050TestResult) {
    console.printf("Test passed \n");
  } else {
    console.printf("Test failed \n");
  }
}

void usb_loop(void const *args)
{
  while(true)
  {
    if( console.readable() )
    {
      led1 = !led1;
      char char1 = console.getc();
      char char2 = console.getc();

      if( char1 == 'R' && char2 == 'X' )
      {
          // Output the scaled values
          console.printf(
            "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
            rx.readThrottle(), rx.readYaw(), rx.readPitch(), rx.readRoll(), 0, 0
          );
      }
      else if( char1 == 'R' && char2 == 'R' )
      {
          // Output the raw values
          console.printf(
            "CH1:%4lu,CH2:%4lu,CH3:%4lu,CH4:%4lu,CH5:%4lu,CH6:%4lu;",
            rx.readChannel(1), rx.readChannel(2), rx.readChannel(3), rx.readChannel(4), 0, 0
          );
      }
      else if( char1 == 'S' && char2 == 'A' )
      {
          // Output the raw values
          mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

          console.printf(
            "AX:%4i,AY:%4i,AZ:%4i,GX:%4i,GY:%4i,GZ:%4i;",
            ax, ay, az, gx, gy, gz
          );
      }
    }
    Thread::wait(20); // 50Hz / 20ms - Currently matching the Rx input speed.
  }
}

void main_loop()
{
  int throttle = rx.readThrottle();
  float output = ((float)throttle/1000000)+0.001;
  motor1.pulsewidth(output);
  motor2.pulsewidth(output);
  motor3.pulsewidth(output);
  motor4.pulsewidth(output);
}

int main()
{
    init();

    Thread usb_thread(usb_loop);
    usb_thread.set_priority(osPriorityLow);

    while(true) {
        main_loop();
        Thread::wait(20); // 50Hz / 20ms - Currently matching the Rx input speed.
    }
}
