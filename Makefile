kernel.img: kernel.elf
	arm-none-eabi-objcopy kernel.elf -O binary kernel.img

CFLAGS	+= -march=armv6 -mtune=arm1176jzf-s -Wall -Wno-psabi -fsigned-char -fno-builtin -nostdinc -nostdlib \
	-std=gnu99
main.o:
	arm-none-eabi-gcc -c main.c -o main.o -Ienvinclude $(CFLAGS)
kernel.elf: main.o
	arm-none-eabi-ld -Tuspienv.ld  startup.o main.o libuspi.a libuspienv.a   -o kernel.elf -Map kernel.map

