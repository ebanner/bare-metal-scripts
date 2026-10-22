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

void init(void) {
    char key[2];

    for (;;) {
        unsigned char result = kbd_poll();
        if (result == 0)
            continue;

        key[0] = result;

        dbg_puts(key);
        dbg_puts("\n");

        usleep(10000);
    }
}
