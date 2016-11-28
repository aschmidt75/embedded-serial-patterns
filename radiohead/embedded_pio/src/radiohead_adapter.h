//
// Created by c018 on 28.11.16.
//

#ifndef EMBEDDED_PIO_RADIOHEAD_ADAPTER_H
#define EMBEDDED_PIO_RADIOHEAD_ADAPTER_H

#include <RHReliableDatagram.h>
#include <RH_Serial.h>

typedef size_t (*radiohead__app_handler_t)(const uint8_t *inbuf, size_t sz_inbuf, uint8_t *outbuf, size_t sz_outbuf);

bool radiohead__loop(RHReliableDatagram *p_datagram_manager, radiohead__app_handler_t app_handler, uint16_t timeout_msec = 500);

#endif //EMBEDDED_PIO_RADIOHEAD_ADAPTER_H
