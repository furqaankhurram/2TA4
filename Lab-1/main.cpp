#include "mbed.h"

InterruptIn userButton(BUTTON1);
DigitalOut led3(PG_13);
DigitalOut led4(PG_14);

int state = 0; //DEFAULT STARTUP STATE
Ticker ticker; // TICKER THAT PERIODICALLY INTERRUPTS THE CODE
int led_timer = 0;    

void SetState() { //CHANGES THE STATE 
    if (state != 1) {
        state = 1;
    } else {
        state = 2;
    }
}

void toggle_leds() {
    if (state == 0) {
        // LED4 SHOULD BLINK EVERY SECOND 
        led4 = !led4;
        }
    else if (state == 1) { //CHECKING STATE, SWITCHES THE LEDs EVERY SECOND
        led4=(led_timer % 2 == 0);
        led3=(led_timer % 2 == 1);
        led_timer++;
        }
    else { //ONE LED ON, THEN BOTH OFF, OTHER ON, THEN BOTH OFF
        led3 = (led_timer % 4 == 0);
        led4 = (led_timer % 4 == 2); 
        led_timer++;
    }
}

int main() {
    userButton.fall(&SetState); //FALLING EDGE OF BUTTON, SWITCHES STATES
    ticker.attach(&toggle_leds, 1s); // CALLS TOGGLE EVERY SECOND
    __enable_irq(); // THIS ENABLES A GLOBAL INTERRUPT

    while (true) {
    }
}

