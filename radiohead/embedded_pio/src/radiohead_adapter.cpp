//
// Created by c018 on 28.11.16.
//

#include "radiohead_adapter.h"

#include "arduino.h"

uint8_t radiohead_in_buf[RH_SERIAL_MAX_MESSAGE_LEN],
        radiohead_out_buf[RH_SERIAL_MAX_MESSAGE_LEN];

/**
 * Loops, reads available datagrams from radiohead Manager, forwards to handler
 * Takes response from handler and sends back as datagram
 * @param timeout_msec Number of msec in call to waitAvailableTimeout
 * @returns true if sucessfull, false in case of I/O error
 */
bool radiohead__loop(RHReliableDatagram *p_datagram_manager, radiohead__app_handler_t app_handler, uint16_t timeout_msec) {

    // Wait for a message addressed to us from the client
    p_datagram_manager->waitAvailableTimeout(timeout_msec);
    if (p_datagram_manager->available())
    {
        bool b_success = false;
        uint8_t len = sizeof(radiohead_in_buf);
        uint8_t from;
        // read into input buffer, get length and from field
        if (p_datagram_manager->recvfromAck(radiohead_in_buf, &len, &from))
        {
            // forward to buffer handling, receive output buffer and length
            uint8_t len_out = (uint8_t) app_handler(radiohead_in_buf, len, radiohead_out_buf,
                                                                   sizeof(radiohead_out_buf));

            if ( len_out > 0) {
                // Send a reply back to the originator client
                if (p_datagram_manager->sendtoWait(radiohead_out_buf, len_out, from)) {
                    b_success = true;
                }
            }
        }

        return b_success;
    }
    return true;
}