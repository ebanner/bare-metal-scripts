static inline void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

int sleep() {
    unsigned int ms = 10000;
    unsigned short divisor = (1193182 * ms) / 1000; // crude, only works for coarse values

    /*
     * Set the PIC to count down
     *
    */
    outb(0x43, 0xB6);  // channel 2, lobyte/hibyte, mode 3 (square wave)
    outb(0x42, divisor & 0xFF);         // low byte -> channel 2 data port
    outb(0x42, (divisor >> 8) & 0xFF);  // high byte -> channel 2 data port

    /*
     * Spin until PIT output pin goes high (channel 0 status)
     *
     */
    while (1) {
        unsigned char status = inb(0x61);
        if (status & 0x20)
            break;
    }
}
