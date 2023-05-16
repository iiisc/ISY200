#include <chrono>
#include "mbed.h"

using namespace std;

SPI ser_port(p11, p12, p13); // mosi, miso, sclk
DigitalOut cs(p14); // Detta är slave-select
AnalogIn pot(p19);

unsigned char switch_word; //word we will send


int main() {
    ser_port.format(8,0); // Setup the SPI for 8 bit data, Mode 0 operation
    ser_port.frequency(1000000); // Clock frequency is 1MHz
    switch_word=0x01; //Skickar en etta

    while (1){
        ser_port.write(switch_word); //Skicka switch_word
        switch_word = pot.read()*100; //Uppdatera switch_word till ett värde mellan 0 och 100. 
        ThisThread::sleep_for(chrono::milliseconds(50));
    }
}
