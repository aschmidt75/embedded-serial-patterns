
#include "serial_packet.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif



void serial_packet_loop(struct serial_packet_handler_s *obj) {
	if (obj->stream->available() > 0) {
        int r = obj->stream->readBytes(obj->p_write, obj->n_remaining);
        obj->n_read += r;
        obj->p_write += r;
        obj->n_remaining -= r;
        if (obj->n_read >= obj->expected_num_bytes) {
            if (obj->handler)
                obj->handler(obj->serial_in_buf, obj->expected_num_bytes);

            // reset
            memset(obj->serial_in_buf,0,sizeof(obj->serial_in_buf));
            obj->p_write = obj->serial_in_buf;
            obj->n_read = 0;
            obj->n_remaining =  obj->expected_num_bytes;
        }
	}
}

bool serial_packet_init(struct serial_packet_handler_s *obj, Stream *s, int packetsize, packet_handler_t hf) {
    if (!s || (packetsize<=0) || (packetsize>=SERIAL_INBUF_MAXSIZE)) {
        return false;
    }

    obj->stream = s;
    memset(obj->serial_in_buf,0,sizeof(obj->serial_in_buf));
    obj->p_write = obj->serial_in_buf;
    obj->expected_num_bytes = packetsize;
    obj->n_read = 0;
    obj->n_remaining = packetsize;
    obj->handler = hf;

    return true;
}

