static inline void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

int mvaddch(int y, int x, const char ch) {
  volatile unsigned short *vga = (volatile unsigned short *)0xB8000;

  int offset = 80*y + x;
  vga[offset] = 0x0F00 | ch; /* 0x0F00 is white on black */

  return 0;
}

static unsigned int CURSOR = 0;

void putchar(const char c) {
  int y = CURSOR / 80;
  int x = CURSOR % 80;

  mvaddch(y, x, c);

  CURSOR += 1;
}

typedef unsigned int useconds_t;

int __usleep(useconds_t usec) {
    /*
     *
     * usec <= 1,000,000
     * 
    */
    unsigned long long divisor = (1193182 * (usec / 1000)) / 1000; // crude, only works for coarse values

    while (divisor > 0) {
        /*
        * Set the PIC to count down
        *
        */
        outb(0x61, (inb(0x61) & ~0x02) | 0x01);  /* gate on, speaker off */
        outb(0x43, 0xB0);                        /* channel 2, mode 0 */
        outb(0x42, 65535 & 0xFF);
        outb(0x42, (65535 >> 8) & 0xFF);

        /*
        * Spin until PIT output pin goes high (channel 0 status)
        *
        */
        while (1) {
            unsigned char status = inb(0x61);
            if (status & 0x20)
                break;
        }

        putchar('x');

        unsigned int chunk = divisor > 65535 ? 65535 : divisor;

        divisor -= chunk;
    }
}

int usleep() {
    useconds_t usec = 1000000;
    
    while (usec > 1000000) {
        __usleep(1000000);
        usec -= 1000000;
    }

    __usleep(usec);
}