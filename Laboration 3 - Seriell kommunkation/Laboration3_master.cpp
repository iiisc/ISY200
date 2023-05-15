#include <chrono>
#include "mbed.h"

using namespace std;

SPI ser_port(p11, p12, p13); // mosi, miso, sclk
DigitalOut cs(p14); // Detta är slave-select
char switch_word; //word we will send

AnalogIn pot(p19);


int checkSpeed(){
    //Läser potentiometer. 1000 vid pot = 0, 300 vid pot = 1. 
    return 400-(300*pot.read());
}

int main() {
    ser_port.format(8,0); // Setup the SPI for 8 bit data, Mode 0 operation
    ser_port.frequency(1000000); // Clock frequency is 1MHz
    switch_word=0x01; //Skickar en etta

    while (1){
        switch_word = ser_port.write(switch_word); //send switch_word and update switch_word with recieved value
        //ThisThread::sleep_for(chrono::microseconds(50))
        ThisThread::sleep_for(chrono::milliseconds(checkSpeed()));
    }
}
