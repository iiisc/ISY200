#include "mbed.h"

PwmOut servo(p5);
//Thread servo_thread;

PwmOut led(p5);
AnalogOut pot(p15);

void svep(int speed) {
    //Om speed = 100 kommer rörelse ett håll ta 1sekund
    servo.period(0.020);
    float start = 0.0009;
    float slut = 0.0021;
    int cycles = 10; //Styr "upplösningen"
    float cycle_time = (slut-start)/cycles;

        for (float i = start; i < slut; i += cycle_time) {
            //Hundra varv i denna loop tar vår servo från min > max
            servo.pulsewidth(i);
            printf("PwmOut: %f, >>Max \n", i);
            wait_ms(speed);
        }
        for (float i = slut; i > start; i -= cycle_time) {
            //Hundra varv i denna loop tar vår servo från max > min
            servo.pulsewidth(i);
            printf("PwmOut: %f, >>Min\n", i); 
            wait_ms(speed);
        }
}

int main() {
    while(1) {
        //servo_thread.start(svep(100));
        //svep(100);
        //printf("Cycle done\n");
        float speed = 50 + (50/pot.read());         
        if (pot.read() < 0.1) {
            speed = 500; 
        }
        printf("Speed: %.3f\n", speed);
        
        wait(0.2);
    }
}