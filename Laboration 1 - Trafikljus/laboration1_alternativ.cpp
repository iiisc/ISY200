#include "mbed.h"

DigitalOut green(LED1);
DigitalOut yellow(LED2);
DigitalOut red(LED3);
DigitalIn btn(BUTTON1);


int main() {
    while (1) {
	green = 1;
	if (btn && green){
		green = 0;
		yellow = 1;
		wait_ms(1000);
	
		yellow = 0;
		red = 1;
		wait_ms(1000);
	}
	if (btn && red){
		yellow = 1;
		wait_ms(1000);
	
		yellow = 0;
		green = 1;
		wait_ms(1000);
	}
    }
}