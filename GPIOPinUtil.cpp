
#include "GPIOPinUtil.h"

#include <Arduino.h>

GPIOPin::GPIOPin(int pin) : pin_(pin) { }

NoPin::NoPin() : GPIOPin(-1) { }

bool NoPin::isOn() {
    return false;
}

void NoPin::on(bool on) { }

ActiveHighPin::ActiveHighPin(int pin) : GPIOPin(pin) { }

bool ActiveHighPin::isOn() {
    pinMode(pin_, INPUT);
    return (digitalRead(pin_) == HIGH);
}

void ActiveHighPin::on(bool on) {
    if(on) {
        digitalWrite(pin_, HIGH);
        pinMode(pin_, OUTPUT);
    } else {
        // instead of writing LOW, we're setting the pin to INPUT to protect the port
        // in case it can be pulled high externally e. g. by a button
        pinMode(pin_, INPUT);
    }
}

ActiveLowPin::ActiveLowPin(int pin) : GPIOPin(pin) { }

bool ActiveLowPin::isOn() {
    pinMode(pin_, INPUT);
    return (digitalRead(pin_) == LOW);
}

void ActiveLowPin::on(bool on) {
    if(on) {
        digitalWrite(pin_, LOW);
        pinMode(pin_, OUTPUT);
    } else {
        // instead of writing HIGH, we're setting the pin to INPUT to protect the port
        // in case it can be pulled low externally e. g. by a button
        pinMode(pin_, INPUT);
    }
}
