#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "serial_packet.h"



struct serial_packet_handler_s	s;

void h(char *buf, int l) {
    //
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println(buf);
}


void setup() {
	Serial.begin(115200);

    serial_packet_init(&s, &Serial, 15, h);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
	serial_packet_loop(&s);
}
