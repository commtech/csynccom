#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
int _kbhit(void);
#endif

#include <synccom.h>

#define DATA_LENGTH 20


int init(synccom_handle h);
int loop(synccom_handle h1, synccom_handle h2);

int main(int argc, char *argv[])
{
    synccom_handle h1, h2;
    int e = 0;
    unsigned port_num_1, port_num_2;
    unsigned reset;
    unsigned iterations = 0;
    unsigned mismatched = 0;

    if (argc < 3 || argc > 4) {
        fprintf(stdout, "%s PORT_NUM PORT_NUM [RESET_REGISTER=1]\n", argv[0]);
        return EXIT_FAILURE;
    }

    port_num_1 = atoi(argv[1]);
    port_num_2 = atoi(argv[2]);
    reset = (argc == 4) ? atoi(argv[3]) : 1;

    e = synccom_connect(port_num_1, &h1);
    if (e != 0) {
        fprintf(stderr, "synccom_connect failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_connect(port_num_2, &h2);
    if (e != 0) {
        fprintf(stderr, "synccom_connect failed with %d\n", e);
        synccom_disconnect(h2);
        return EXIT_FAILURE;
    }

    if (reset) {
        e = init(h1);
        if (e != 0) {
            synccom_disconnect(h1);
            synccom_disconnect(h2);
            return EXIT_FAILURE;
        }

        e = init(h2);
        if (e != 0) {
            synccom_disconnect(h1);
            synccom_disconnect(h2);
            return EXIT_FAILURE;
        }
    }

    fprintf(stdout, "Data looping, press any key to stop...\n");

    while (_kbhit() == 0) {
        e = loop(h1, h2);
        if (e != 0) {
            if (e == -1) {
                mismatched++;
            }
            else {
                synccom_disconnect(h1);
                synccom_disconnect(h2);
                return EXIT_FAILURE;
            }
        }

        iterations++;
    }

    if (mismatched == 0)
        fprintf(stdout, "Passed (%d iterations).\n", iterations);
    else
        fprintf(stderr, "Failed (%d out of %d iterations).\n",
                mismatched, iterations);

    synccom_disconnect(h1);
    synccom_disconnect(h2);

    return EXIT_SUCCESS;
}

int init(synccom_handle h)
{
    struct synccom_registers r;
    struct synccom_memory_cap m;
    int e = 0;

    m.input = 1000000;
    m.output = 1000000;

    e = synccom_set_memory_cap(h, &m);
    if (e != 0) {
        fprintf(stderr, "synccom_set_memory_cap failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_disable_rx_multiple(h);
    if (e != 0) {
        fprintf(stderr, "synccom_disable_rx_multiple failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_disable_append_status(h);
    if (e != 0) {
        fprintf(stderr, "synccom_disable_append_status failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_disable_append_timestamp(h);
    if (e != 0) {
        fprintf(stderr, "synccom_disable_append_timestamp failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_set_tx_modifiers(h, XF);
    if (e != 0) {
        fprintf(stderr, "synccom_set_tx_modifiers failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_disable_ignore_timeout(h);
    if (e != 0) {
        fprintf(stderr, "synccom_disable_ignore_timeout failed with %d\n", e);
        return EXIT_FAILURE;
    }

    SYNCCOM_REGISTERS_INIT(r);

    r.FIFOT = 0x08001000;
    r.CCR0 = 0x0011201c;
    r.CCR1 = 0x00000018;
    r.CCR2 = 0x00000000;
    r.BGR = 0x00000000;
    r.SSR = 0x0000007e;
    r.SMR = 0x00000000;
    r.TSR = 0x0000007e;
    r.TMR = 0x00000000;
    r.RAR = 0x00000000;
    r.RAMR = 0x00000000;
    r.PPR = 0x00000000;
    r.TCR = 0x00000000;
    r.IMR = 0x0f000000;
    r.DPLLR = 0x00000004;
    r.FCR = 0x00000000;

    e = synccom_set_registers(h, &r);
    if (e != 0) {
        fprintf(stderr, "synccom_set_registers failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_set_clock_frequency(h, 18432000);
    if (e != 0) {
        fprintf(stderr, "synccom_set_clock_frequency failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_purge(h, 1, 1);
    if (e != 0) {
        fprintf(stderr, "synccom_purge failed with %d\n", e);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int loop(synccom_handle h1, synccom_handle h2)
{
    unsigned bytes_written = 0, bytes_read = 0;
    char odata[DATA_LENGTH];
    char idata[100];
    int e = 0;

    memset(&odata, 0x01, sizeof(odata));
    memset(&idata, 0, sizeof(idata));

    e = synccom_write_with_blocking(h1, odata, sizeof(odata), &bytes_written);
    if (e != 0) {
        fprintf(stderr, "synccom_write_with_blocking failed with %d\n", e);
        return EXIT_FAILURE;
    }

    e = synccom_read_with_timeout(h2, idata, sizeof(idata), &bytes_read, 1000);
    if (e != 0) {
        fprintf(stderr, "synccom_read_with_timeout failed with %d\n", e);
        return EXIT_FAILURE;
    }

    if (bytes_read == 0 || memcmp(odata, idata, sizeof(odata)) != 0)
        return -1;

    return EXIT_SUCCESS;
}

#ifndef _WIN32
int _kbhit(void) {
    static const int STDIN = 0;
    static unsigned initialized = 0;
    int bytes_waiting;

    if (!initialized) {
        /* Use termios to turn off line buffering */
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

    ioctl(STDIN, FIONREAD, &bytes_waiting);
    return bytes_waiting;
}
#endif