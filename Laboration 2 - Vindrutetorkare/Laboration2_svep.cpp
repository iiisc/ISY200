#include "mbed.h"
#include <chrono>

using namespace std;

PwmOut red(p23);
PwmOut green(p24);
PwmOut blue(p25);
PwmOut servo(p22);
AnalogIn pot(p19);
BusIn joystick(p15, p12, p16, p13);

bool wiperQuick;
bool wiperSlow;
bool wiperInterval;

int checkSpeed(){
    //Läser potentiometer. 1000 vid pot = 0, 300 vid pot = 1. 
    return 1000-(700*pot.read());
}

void checkState(){
   
  switch(joystick) {
    case 0x1: 
        wiperQuick = true; red = 0.95;
        wiperSlow = false; blue = 1.0;
        wiperInterval = false; green = 1.0;
        break; // 0 0 0 1
        
    case 0x2:
        wiperQuick = false; red = 1.0;
        wiperSlow = true; blue = 0.95;
        wiperInterval = false; green = 1.0;
        break; // 0 0 1 0
        
    case 0x4:
        wiperQuick = false; red = 1.0;
        wiperSlow = false; blue = 1.0;
        wiperInterval = true; green = 0.95;
        break; // 0 1 0 0 
        
    case 0x8:
        wiperQuick = false; red = 1.0;
        wiperSlow = false; blue = 1.0;
        wiperInterval = false; green = 1.0;
        break; // 1 0 0 0
    }  
}

void svep(int speed) {
    //Om speed = 100 kommer rörelse ett håll ta 1sekund
    float start = 0.0009;
    float slut = 0.0021;
    int cycles = 100;
    float cycle_time = (slut-start)/cycles;
    
        for (float i = start; i < slut; i += cycle_time) {
            //Hundra varv i denna loop tar vår servo från min > max
            servo.pulsewidth(i);
            checkState();
            ThisThread::sleep_for(chrono::milliseconds(speed/10));

        }
        for (float i = slut; i > start; i -= cycle_time) {
            //Hundra varv i denna loop tar vår servo från max > min
            servo.pulsewidth(i);
            checkState();
            ThisThread::sleep_for(chrono::milliseconds(speed/10));
        }
}

void svepInterval(int speed){
        for (int i = 0; i < 10; i++){
            //Grön lampa blinkar som styrs av potentiometer (se checkSpeed())
            checkState();
            green = !green;
            ThisThread::sleep_for(chrono::milliseconds(checkSpeed()/2));
        }
        svep(speed);
        green = 1.0;
}

int main() {
    servo.period(0.020);

    while(1) {
        checkState();
        
        if (wiperQuick || wiperSlow || wiperInterval){
            if (wiperQuick){
                svep(100);
            }
            if (wiperSlow){
                svep(300);
            }
            if (wiperInterval){
                svepInterval(100);
            }
        }
        ThisThread::sleep_for(chrono::milliseconds(10));
    }
}
