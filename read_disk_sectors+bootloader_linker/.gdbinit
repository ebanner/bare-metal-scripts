# ---- connect + symbols -------------------------------------------------------
file boot_sector.elf
target remote :1234

# ---- start in real mode (boot sector) ----------------------------------------
set architecture i8086
set disassemble-next-line off
layout split
directory .

# ---- breakpoints -------------------------------------------------------
break *0x7C00
tbreak my_bp
continue
