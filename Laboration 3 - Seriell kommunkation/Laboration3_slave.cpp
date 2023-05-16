#include "mbed.h"
#include <chrono>

SPISlave slave(p11, p12, p13, p14); // mosi, miso, sclk ssel
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
unsigned char input;

void lamps(int speed){
    // Speed är initialt ett värde mellan 0 och 100. 
    int wait_time = 400-(speed*3.95); //Som snabbast 100ms, som långsamast 300ms.
    led1 = 1;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    ThisThread::sleep_for(chrono::milliseconds(wait_time));
    led1 = 0;
    led2 = 1;
    led3 = 0;
    led4 = 0;
    ThisThread::sleep_for(chrono::milliseconds(wait_time));
    led1 = 0;
    led2 = 0;
    led3 = 1;
    led4 = 0;
    ThisThread::sleep_for(chrono::milliseconds(wait_time));
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 1;
    ThisThread::sleep_for(chrono::milliseconds(wait_time));
}

int main()
{

    slave.format(8,0);
    slave.frequency(1000000);
    led1 = 0; led2 = 0; led3 = 0; led4 = 0; //Släck alla lampor

    while (1) {
        
        if (slave.receive()) {
        input = slave.read(); // Läs från master
        slave.reply(0x01);
        lamps(input);
        }
        ThisThread::sleep_for(chrono::milliseconds(50));
    }
}
