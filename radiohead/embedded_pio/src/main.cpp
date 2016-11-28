#include "Arduino.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#include <RadioHead.h>
#include <RHReliableDatagram.h>
#include <RH_Serial.h>
#include "radiohead_adapter.h"


#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2


// On arduino etc, use a predefined local serial port
// eg Serial1 on a Mega
#include <SPI.h>
// Singleton instance of the Serial driver, configured
// to use the port Serial1. Caution: on Uno32, Serial1 is on pins 39 (Rx) and
// 40 (Tx)
RH_Serial driver(Serial);


// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, SERVER_ADDRESS);

void _flash(int rep, int wait) {
    for ( int i = 0; i < rep; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(wait);
        digitalWrite(LED_BUILTIN, LOW);
        delay(wait);
    }
}
void _fast_flash() {
    _flash(20,50);
}

void setup() {
    // initialize Pins
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Configure the port RH_Serial will use:
    driver.serial().begin(115200);
    if (!manager.init()) {
        _fast_flash();
    }
}

size_t sample_app_handler_t(const uint8_t *inbuf, size_t sz_inbuf, uint8_t *outbuf, size_t sz_outbuf) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);

    // copy over
    memcpy(outbuf, inbuf, sz_inbuf);
    return sz_inbuf;
}

void loop() {
    radiohead__loop(&manager, &sample_app_handler_t);
}