#ifndef __SERIAL_PACKET_H
#define __SERIAL_PACKET_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif


const int SERIAL_INBUF_MAXSIZE = 512;

typedef void (*packet_handler_t)(char *buf, int len);

struct serial_packet_handler_s {
	Stream *stream;

    // input buffer
	char serial_in_buf[SERIAL_INBUF_MAXSIZE];

    // write pointer
    char *p_write = (char*)0;

    // number of bytes alread read
    int n_read = 0;

    // number of bytes still expected
    int n_remaining = 0;

    // number of bytes expected
    int expected_num_bytes = 0;

    packet_handler_t  handler;

};

void serial_packet_loop(struct serial_packet_handler_s *obj);

bool serial_packet_init(struct serial_packet_handler_s *obj, Stream *s, int packetsize, packet_handler_t hf);

#endif      // __SERIAL_PACKET_H