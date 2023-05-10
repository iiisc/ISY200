#include "mbed.h"

PwmOut servo(p5);
//Thread servo_thread;

PwmOut led(p5);
AnalogOut pot(p15);
BusIn joystick(p6, p7, p8, p9);

float checkSpeed(){
    return 500-(400*pot.read());
}

void svep() {
    //Om speed = 100 kommer rörelse ett håll ta 1sekund
    servo.period(0.020);
    float start = 0.0009;
    float slut = 0.0021;
    int cycles = 10; //Styr "upplösningen"
    float cycle_time = (slut-start)/cycles;
    
    float speed = checkSpeed();

        for (float i = start; i < slut; i += cycle_time) {
            //Hundra varv i denna loop tar vår servo från min > max
            //printf("PwmOut: %f, Speed: %f, >>Max \n", i, speed);
            servo.pulsewidth(i);
            float speed = checkSpeed();
            wait_ms(speed);
        }
        for (float i = slut; i > start; i -= cycle_time) {
            //Hundra varv i denna loop tar vår servo från max > min
            //printf("PwmOut: %f, Speed: %f, >>Min\n", i, speed); 
            servo.pulsewidth(i);
            float speed = checkSpeed();
            wait_ms(speed);
        }
        printf("Svep done\n");
}

bool wiperOn;

int main() {
    while(1) {
        //servo_thread.start(svep(100));
        //svep();
        switch(joystick) {
            case 0x1: 
                printf("Case 0x1! p6\n"); 
                wiperOn = true;
                break; // 0 0 0 1
                
            case 0x2: printf("Case 0x2! p7\n"); 
                wiperOn = false;
                break; // 0 0 1 0
                
            case 0x4: printf("Case 0x4! p8\n"); 
                break; // 0 1 0 0 
                
            case 0x8: printf("Case 0x8! p9\n"); 
                break; // 1 0 0 0
        }
        
        if (wiperOn) {
            svep();
        }
        
        wait(0.05);
    }
}