debug: os.img
	qemu-system-i386 -S -s -monitor stdio -vga std -display cocoa,zoom-to-fit=on os.img

run: os.img
	qemu-system-i386 -s -monitor stdio os.img

run: os.img
	qemu-system-i386 -monitor stdio os.img

boot_asm.o: boot.asm
	nasm -f elf32 -g -F dwarf boot.asm -o boot_asm.o

boot_c.o: boot.c
	i686-elf-gcc \
		-m32 \
		-ffreestanding \
		-fno-pic \
		-fno-stack-protector \
		-nostdlib \
		-O0 \
		-g \
		-c boot.c \
		-o boot_c.o

init.o: init.c
	i686-elf-gcc \
		-m32 \
		-ffreestanding \
		-fno-pic \
		-fno-stack-protector \
		-nostdlib \
		-O0 \
		-g \
		-c init.c \
		-o init.o

os.elf: boot_asm.o boot_c.o init.o
	i686-elf-ld \
		-m elf_i386 \
		-T link.ld \
		-o os.elf \
		boot_asm.o \
		boot_c.o \
		init.o \

os.img: os.elf
	i686-elf-objcopy -O binary os.elf os.img

docker:
	# docker build -t doom-os .
	docker run -it --rm -v $(CURDIR):/src doom-os

clean:
	rm -f *.o *.elf *.bin *.img
