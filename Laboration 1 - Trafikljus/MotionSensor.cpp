#include "mbed.h"

// main() runs in its own thread in the OS
DigitalOut green(p8);
DigitalOut yellow(p7);
DigitalOut red(p6);
DigitalIn btn(p5);

int main()
{
    while (true) {

        btn.mode(PullDown);
        if (btn) {
        red = 0;
        yellow = 0;
        green = 1;
        ThisThread::sleep_for(50ms);
        yellow = !yellow;
        green = !green;
        ThisThread::sleep_for(50ms);
        yellow = !yellow;
        red = !red;
        ThisThread::sleep_for(50ms);
        } else {
        green = 0;
        red = 0;
        yellow = 0;
        }
    }
}
