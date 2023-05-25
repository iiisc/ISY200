#include "mbed.h"
#include "C12832A1Z.h"
#include <chrono>

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
AnalogIn pot(p19);
AnalogIn pot2(p20);

InterruptIn btnUp(p15);
InterruptIn btnDown(p12);
C12832A1Z lcd(p5, p7, p6, p8, p11);
PwmOut speaker(p26);

Ticker bpm_ticker;
Timeout sound_duration;
Timeout LCD_ticker;
Timer debounce;

int BPM = 20;
float sound;

void quiet(){
    led1=0;
    speaker = 0.0;
}

void tick() {
    led1 = 1;
    //Startar speaker med 500Hz och volym 0.5. startar även en timeout som ska stänga av ljudet via quiet();
    speaker = sound;
    sound_duration.attach(&quiet, chrono::milliseconds(100));
}

void update_LCD(){
    led4 = !led4;
    lcd.locate(1,0);
    lcd.printf("%d", BPM);
}

void increase_speed() {
    if (debounce.read_ms() > 100) {
    BPM += 4;
    led3 = !led3;
    bpm_ticker.attach(&tick, chrono::milliseconds(60000/BPM));
    debounce.reset();
    }
}

void decrease_speed() {
    if (debounce.read_ms() > 100 && BPM > 4) {
    BPM -= 4;
    led2 = !led2;
    bpm_ticker.attach(&tick, chrono::milliseconds(60000/BPM));
    debounce.reset();
    }
}

int main() {
    speaker.period(1.0/500);
    debounce.start();

    bpm_ticker.attach(&tick, chrono::milliseconds(BPM*100));
    btnUp.fall(&increase_speed);
    btnDown.fall(&decrease_speed);

    while(1) {
    sound=pot2.read()/2;
    speaker.period(1/(500+(pot.read()*3500)));
    lcd.update();
    lcd.locate(0,3);
    lcd.printf("Metronom: %d", BPM);
    ThisThread::sleep_for(chrono::milliseconds(100));
    }
}
