#include "mbed.h"

PwmOut servo(p5);
//Thread servo_thread;

PwmOut led(p5);
AnalogOut pot(p15);

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
            servo.pulsewidth(i);
            float speed = checkSpeed();
            printf("PwmOut: %f, Speed: %f, >>Max \n", i, speed);
            wait_ms(speed);
        }
        for (float i = slut; i > start; i -= cycle_time) {
            //Hundra varv i denna loop tar vår servo från max > min
            servo.pulsewidth(i);
            float speed = checkSpeed();
            printf("PwmOut: %f, Speed: %f, >>Min\n", i, speed); 
            wait_ms(speed);
        }
}

int main() {
    while(1) {
        //servo_thread.start(svep(100));
        svep();
        printf("Cycle done\n");
        wait(4);
    }
}