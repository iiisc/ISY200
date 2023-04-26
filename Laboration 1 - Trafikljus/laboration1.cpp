#include "mbed.h"

DigitalOut green(LED1);
DigitalOut yellow(LED2);
DigitalOut red(LED3);

int main() {
    while (1) {
        green = 1;
        
        if (green){
            green = 0;
            yellow = 1;
            red = 0;  
            wait_ms(900);
        }
        if (yellow){
            green = 0;
            yellow = 0;
            red = 1;  
            wait_ms(900);
        }
        if (red){
            green = 0;
            yellow = 1;
            red = 1;
            wait_ms(900);
        }
        if (red && yellow){
            green = 1;
            yellow = 0;
            red = 0;
            wait_ms(900);
        }
    }
}