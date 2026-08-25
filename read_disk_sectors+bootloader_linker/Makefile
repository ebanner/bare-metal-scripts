debug: boot.img
	qemu-system-i386 -S -s -monitor stdio boot.img

boot.img: boot_sector.img
	head -c 1024 boot_sector.img > boot.img
	tr '\0' 'E' < /dev/zero | dd bs=1 count=512 2>/dev/null >> boot.img

boot_sector.img: boot_sector.elf
	i686-elf-objcopy -O binary boot_sector.elf boot_sector.img

boot_sector.elf: boot_sector.o
	i686-elf-ld \
		-m elf_i386 \
		-T link.ld \
		-o boot_sector.elf \
		boot_sector.o \

boot_sector.o: boot_sector.asm
	nasm -f elf32 -g -F dwarf boot_sector.asm -o boot_sector.o

clean:
	rm -f *.o *.elf *.img *.bin

