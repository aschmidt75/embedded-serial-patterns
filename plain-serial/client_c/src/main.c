#include "Arduino.h"
#include "arduino-serial-lib.h"

char	buf[128];

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "PROGRAM <SERIALPORT>\n./b");
        exit(1);
    }
    // open serial port
    int fd = serialport_init(argv[1], 115200);

    // If it's an Arduino: delay a bit, because arduino uno resets when opening serial..
    sleep(2);

    // write to serial
    strcpy(buf,"123456789012345");
    // 15=sample packet size
    write(fd, buf, 15);

    sleep(1);

    // read response
    memset(buf,0,sizeof(buf));
    int num_read = read(fd, buf, sizeof(buf));
    printf("num_read=%i, buf=%s", num_read, buf);

    serialport_close(fd);
}
