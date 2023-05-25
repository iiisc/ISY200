#include "mbed.h"
#include "C12832.h"

DigitalOut led1(LED1);
InterruptIn btnUp(p15);
InterruptIn btnDown(p12);
C12832 lcd(p5, p7, p6, p8, p11);
PwmOut speaker(p26);

Ticker bpm_ticker;
Timeout sound_duration;
Timeout update_LCD_timeout;
Timer debounce;

int BPM = 20; //Startar med 20BPM

void quiet(){
    speaker = 0.0;
}

void tick() {
    //printf("Ticker fired, Time between ticks: %.2f. BPM: %.2f \n", 60/BPM, BPM);
    led1 = !led1;
    //Startar speaker med 500Hz och volym 0.5. startar även en timeout som ska stänga av ljudet via quiet();
    speaker.period(1.0/500);
    speaker = 0.5;
    sound_duration.attach(&quiet, 0.1);
}

void update_LCD(){
    lcd.cls();
    lcd.locate(0,3);
    lcd.printf("Metronom. BPM: %d", BPM);
}

void increase_speed() {
    if (debounce.read_ms() > 100) {
    BPM += 4;
    bpm_ticker.detach();
    bpm_ticker.attach(&tick, 60/BPM);
    update_LCD_timeout.attach(&update_LCD, 0.2);
    debounce.reset();
    }
}

void decrease_speed() {
    if (debounce.read_ms() > 100) {
    BPM -= 4;
    bpm_ticker.detach();
    bpm_ticker.attach(&tick, 60/BPM);
    update_LCD_timeout.attach(&update_LCD, 0.2);
    debounce.reset();
    }
}


int main() {

    debounce.start();
    bpm_ticker.attach(&tick, BPM);
    btnUp.fall(&increase_speed);
    btnDown.fall(&decrease_speed);

    while(1) {
    ThisThread::sleep_for(chrono::milliseconds(50));
    }
}
