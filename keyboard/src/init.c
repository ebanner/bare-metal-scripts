#include <unistd.h>
#include <debug.h>

static inline unsigned char inb(unsigned short port) {
    unsigned char v;
    __asm__ volatile ("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

unsigned int kbd_poll() {
    unsigned char status = inb(0x64);
    if (status & 0x01 == 0)
        return 0;

    unsigned char key = inb(0x60);
    return key;
}

char* itoa(int value, char *buf) {
    char *p = buf;
    unsigned int u = (unsigned int)value;

    if (value < 0)
        u = -u;

    do {
        *p++ = '0' + (u % 10);
        u /= 10;
    } while (u != 0);

    if (value < 0)
        *p++ = '-';

    *p = '\0';

    // reverse in place
    for (char *a = buf, *b = p - 1; a < b; a++, b--) {
        char t = *a; *a = *b; *b = t;
    }

    return buf;
}

void init(void) {
    char buf[12];

    for (;;) {
        unsigned int result = kbd_poll();
        if (result == 0)
            continue;

        if (result != 0x39)
            continue;

        dbg_puts("Space!\n");

        usleep(10000);
    }
}
