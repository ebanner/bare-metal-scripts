debug: os.img
	qemu-system-i386 -s \
		-debugcon stdio \
		-vga std \
		-display cocoa,zoom-to-fit=on \
		os.img

# debug2: os.img
# 	qemu-system-i386 \
# 		-S \
# 		-s \
# 		-monitor stdio \
# 		-vga std \
# 		-display cocoa,zoom-to-fit=on \
# 		os.img

run: os.img
	qemu-system-i386 -s -monitor stdio os.img

run: os.img
	qemu-system-i386 -monitor stdio os.img

src/boot_asm.o: src/boot.asm
	nasm -f elf32 -g -F dwarf src/boot.asm -o src/boot_asm.o

LIB_SRC := $(wildcard src/lib/*.c)
LIB_OBJ := $(LIB_SRC:.c=.o)

src/boot_c.o: src/boot.c
	i686-elf-gcc \
		-m32 \
		-ffreestanding \
		-fno-pic \
		-fno-stack-protector \
		-nostdlib \
		-O0 \
		-g \
		-c src/boot.c \
		-o src/boot_c.o

src/init.o: src/init.c
	i686-elf-gcc \
		-m32 \
		-ffreestanding \
		-fno-pic \
		-fno-stack-protector \
		-nostdlib \
		-Isrc/lib \
		-O0 \
		-g \
		-c src/init.c \
		-o src/init.o

src/lib/%.o: src/lib/%.c
	i686-elf-gcc \
		-m32 \
		-ffreestanding \
		-fno-pic \
		-fno-stack-protector \
		-nostdlib \
		-nostdinc \
		-fno-builtin \
		-O0 \
		-g \
		-c $< \
		-o $@ \
		# -std=c99 \

os.elf: src/boot_asm.o src/boot_c.o src/init.o $(LIB_OBJ)
	i686-elf-ld \
		-m elf_i386 \
		-T link.ld \
		-o os.elf \
		src/boot_asm.o \
		src/boot_c.o \
		src/init.o \
		$(LIB_OBJ)

os.img: os.elf
	i686-elf-objcopy -O binary os.elf os.img

docker:
	# docker build -t doom-os .
	docker run -it --rm -v $(CURDIR):/src doom-os

clean:
	rm -f src/*.o *.elf *.bin *.img src/*.o src/lib/*.o
