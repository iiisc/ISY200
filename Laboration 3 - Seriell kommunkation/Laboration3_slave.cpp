#include "mbed.h"

SPISlave slave(p11, p12, p13, p14); // mosi, miso, sclk, ssel
DigitalOutput led1(LED1);
DigitalOutput led2(LED2);
DigitalOutput led3(LED3);
DigitalOutput led4(LED4);


void lamps(int speed){
    // Speed är initialt ett värde mellan 0 och 100. 
    wait_time = 300-(speed*2) //Som snabbast 100ms, som långsamast 300ms.

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
    slave.format(8.0);
    slave.frequency(1000000);
    slave.reply(0x01); // Första svaret
    
    unsigned char output = 0x01; // Det ständiga svaret. En etta. 
    led1 = 0; led2 = 0; led3 = 0; led4 = 0; //Släck alla lampor

    while (1) {
        if (slave.receive()) {
            int input = slave.read(); // Läs från master. Kommer vara ett värde mellan 0 och 100
            slave.reply(output); // Skicka tillbaka till master
            lamps(input);
            ThisThread::sleep_for(chrono::milliseconds(50));
        }
    }
}
