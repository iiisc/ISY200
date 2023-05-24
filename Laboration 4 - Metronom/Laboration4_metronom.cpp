#include "mbed.h"
#include "C12832.h"

DigitalOut led1(LED1);
InterruptIn btnUp(p15); //Vet inte vilka pinnar som är vilka här. Rätta till det på plats. Viktor vet säkert ;)
InterruptIn btnDown(p12); //Vet inte vilka pinnar som är vilka här. Rätta till det på plats. Viktor vet säkert ;)
C12832 lcd(p5, p7, p6, p8, p11); //LCD skärmen kanske?

Ticker bpm_ticker;
Timeout sound_duration;
Timeout update_LCD;

float BPM = 20; //Startar med 20BPM

void tick() {
    //printf("Ticker fired, Time between ticks: %.2f. BPM: %.2f \n", 60/BPM, BPM);
    led1 = !led1;
    //Startar speaker med 500Hz och volym 0.35. startar även en timeout som ska stänga av ljudet via quiet();
    speaker.period(1/500);
    speaker = 0.5
    sound_duration.attach(&quiet, 0.1)
}

void quiet(){
    speaker = 0.0;
}

void update_LCD(){
    lcd.cls();
    lcd.locate(0,3);
    lcd.prinf("Metronom. BPM: %d", BPM);
}

void increase_speed() {
    BPM += 4;
    bpm_ticker.detach();
    bpm_ticker.attach(&tick, 60/BPM);
    update_LCD.attach(&update_LCD, 0.2);
}

void decrease_speed() {
    BPM -= 4;
    bpm_ticker.detach();
    bpm_ticker.attach(&tick, 60/BPM);
    update_LCD.attach(&update_LCD, 0.2);
}


int main() {

    bpm_ticker.attach(&tick, BPM);
    btn.fall(&increase_speed);

    ThisThread::sleep_for(chrono::milliseconds(50));
}
