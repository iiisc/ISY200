#include "mbed.h"

SPISlave device(p11, p12, p13, p14); // mosi, miso, sclk, ssel
DigitalOutput led1(LED1);
DigitalOutput led2(LED2);
DigitalOutput led3(LED3);


int main()
{
    device.format(8.0);
    device.frequency(1000000);
    device.reply(0x00);              // Prime SPI with first reply

    while (1) {
        if (device.receive()) {
            int input = device.read();   // Read byte from master
            input = (input+1) % 3;     // Går från 0 till 2
            device.reply(v);         // Make this the next reply
        }
        if (input == 0) {
            led1 = 1;
            led2 = 0;
            led3 = 0;

        }
        if (input == 1) {
            led1 = 0;
            led2 = 1;
            led3 = 0;
        }
        if (input == 2) {
            led1 = 0;
            led2 = 0;
            led3 = 1;
        }
    }
}
