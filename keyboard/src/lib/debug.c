static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void dbg_putc(char c) { outb(0xE9, (unsigned char)c); }

void dbg_puts(const char *s) {
    while (*s) dbg_putc(*s++);
}