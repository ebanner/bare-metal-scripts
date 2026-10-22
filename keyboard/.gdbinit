target remote :1234
symbol-file os.elf

layout split
directory .

# break *0x7C00
tbreak pm_entry
continue
