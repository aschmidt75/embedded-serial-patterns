#include <stdio.h>

// serial_reliable_datagram_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RHReliableDatagram class, using the RH_Serial driver to
// communicate using packets over a serial port (or a radio connected to a
// serial port, such as the 3DR Telemetry radio V1 and others).
// It is designed to work with the other example serial_reliable_datagram_server
// Tested on Arduino Mega and ChipKit Uno32 (normal Arduinos only have one
// serial port and so it not possible to test on them and still have debug
// output)
// Tested with Arduino Mega, Teensy 3.1, Moteino, Arduino Due
// Also works on Linux and OSX. Build and test with:
//  tools/simBuild examples/serial/serial_reliable_datagram_client/serial_reliable_datagram_client.pde
//  RH_HARDWARESERIAL_DEVICE_NAME=/dev/ttyUSB1 ./serial_reliable_datagram_client

#include "Arduino.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <RadioHead.h>
#include <RHReliableDatagram.h>


#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

#include <RHutil/HardwareSerial.h>
#include <RH_Serial.h>

// On Unix we connect to a physical serial port
// You can override this with RH_HARDWARESERIAL_DEVICE_NAME environment variable
//HardwareSerial hardwareserial("/dev/tty.usbmodem1411");
//RH_Serial driver(hardwareserial);

// Class to manage message delivery and receipt, using the driver declared above
//RHReliableDatagram manager(driver, CLIENT_ADDRESS);

// Dont put this on the stack:
uint8_t buf[RH_SERIAL_MAX_MESSAGE_LEN];



unsigned long millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long int)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void delay(unsigned long l) {
    usleep(l*1000);
}

long random(long l1, long l2) {
    return l1+rand()%(l2-l1);
}

void hexDump (const char *desc, uint8_t *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

void single_call(RHReliableDatagram *p_manager, const char *inp_str) {
    size_t sz_out_data = strlen(inp_str);
    memcpy(buf,inp_str,sz_out_data);

    hexDump("Request", &buf[0], sz_out_data);

    if (p_manager->sendtoWait(buf, sizeof(buf), SERVER_ADDRESS))
    {
        // Now wait for a reply from the server
        uint8_t len = sizeof(buf);
        uint8_t from;

        if (p_manager->recvfromAckTimeout(buf, &len, 2000, &from))
        {
            hexDump("Reply", &buf[0], len);
        }
        else
        {
            printf("No reply, is serial_reliable_datagram_server running?\n");
        }
    }
    else
        printf("sendtoWait failed\n");


}

int main(int argc, char** argv) {
    srand(time(NULL));

    if ( argc < 2) {
        printf("Use radiohead1 <serialdevice>\n");
        return (1);
    }
    HardwareSerial *p_hardwareserial = new HardwareSerial(argv[1]);//("/dev/tty.usbmodem1411");
    RH_Serial *p_driver = new RH_Serial(*p_hardwareserial);

    // Configure the port RH_Serial will use:
    p_driver->serial().begin(115200);

    // Class to manage message delivery and receipt, using the driver declared above
    RHReliableDatagram manager(*p_driver, CLIENT_ADDRESS);
    if (!manager.init()) {
    	printf("init failed\n");
	return(2);
    }

    single_call(&manager, "1234567890123");

    printf("Done.\n");fflush(stdout);
}

