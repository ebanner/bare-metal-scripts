OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

SECTIONS {
  /* Boot sector */

  . = 0x7C00;

  .text : {
    boot*(.text*)
  }
  .rodata : {
    boot*(.rodata*)
  }
  .data : {
    boot*(.data*)
  }
  .bss : {
    boot*(.bss*) boot*(COMMON)
  }

  .text : {
    init*(.text*)
  }
  .rodata : {
    init*(.rodata*)
  }
  .data : {
    init*(.data*)
  }
  .bss : {
    init*(.bss*) init*(COMMON)
  }

  /* Pad to 510 bytes and add boot signature */
  . = 0x7C00 + 510;
  
  .bootsig : {
    SHORT(0xAA55)
  }

}
