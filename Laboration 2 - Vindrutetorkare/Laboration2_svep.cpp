#include "mbed.h"

PwmOut red(p23);
PwmOut green(p24);
PwmOut blue(p25);

PwmOut servo(p5);

AnalogOut pot(p15);
BusIn joystick(p6, p7, p8, p9);

bool wiperQuick;
bool wiperSlow;
bool wiperInterval;

float checkSpeed(){
    //Läser potentiometer. 1000 vid pot = 0, 300 vid pot = 1. 
    return 1000-(700*pot.read());
}

void checkState(){
  switch(joystick) {
    case 0x1: 
        printf("Case 0x1! p6\n"); 
        wiperQuick = true; red = 0.5;
        wiperSlow = false; blue = 0.0;
        wiperInterval = false; green = 0.0;
        break; // 0 0 0 1
        
    case 0x2: printf("Case 0x2! p7\n"); 
        wiperQuick = false; red = 0.0;
        wiperSlow = true; blue = 0.5;
        wiperInterval = false; 
        break; // 0 0 1 0
        
    case 0x4: printf("Case 0x4! p8\n"); 
        wiperQuick = false; red = 0.0;
        wiperSlow = false; blue = 0.0;
        wiperInterval = true; green = 0.5; //Ska egentligen blinka, detta får vi fixa sen
        break; // 0 1 0 0 
        
    case 0x8: printf("Case 0x8! p9\n"); 
        wiperQuick = false; red = 0.0;
        wiperSlow = false; blue = 0.0;
        wiperInterval = false; green = 0.0;
        break; // 1 0 0 0
    }  
}

void svep(float speed) {
    //Om speed = 100 kommer rörelse ett håll ta 1sekund
    servo.period(0.020);
    float start = 0.0009;
    float slut = 0.0021;
    int cycles = 10; //Styr "upplösningen"
    float cycle_time = (slut-start)/cycles;
    
        for (float i = start; i < slut; i += cycle_time) {
            //Hundra varv i denna loop tar vår servo från min > max
            //printf("PwmOut: %f, Speed: %f, >>Max \n", i, speed);
            servo.pulsewidth(i);
            checkState();
            wait_ms(speed);
        }
        for (float i = slut; i > start; i -= cycle_time) {
            //Hundra varv i denna loop tar vår servo från max > min
            //printf("PwmOut: %f, Speed: %f, >>Min\n", i, speed); 
            servo.pulsewidth(i);
            checkState();
            wait_ms(speed);
        }
        printf("Svep done\n");
}

void svepInterval(float speed){
        for (int i = 0; i < 10; i++){
            //Grön lampa blinkar som styrs av potentiometer (se checkSpeed())
            printf("i: %d: lamp: %f\n", i, green.read());
            checkState();
            green = !green;
            wait_ms(checkSpeed()/2);
        }
        svep(speed);
        green = 0.0;
}

int main() {
    while(1) {

        checkState();
        
        if (wiperQuick || wiperSlow || wiperInterval){
            printf("State: Wiperquick: %d, WiperSlow: %d, WiperInterval: %d\n", wiperQuick, wiperSlow, wiperInterval);
            if (wiperQuick){
                //Lampa röd
                svep(100);
            }
            if (wiperSlow){
                //Lampa blå
                svep(300);
            }
            if (wiperInterval){
                //Lampa grön blinkar med pot hastighet
                svepInterval(100);
            }
        }

        checkState();
        wait(0.05);
    }
}