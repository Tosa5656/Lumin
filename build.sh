gcc -m16 -ffreestanding -nostdlib -c src/kernel.c -o obj/kernel.o
ld -m elf_i386 -T src/kernel-linker.ld -o bin/kernel.bin obj/kernel.o
objcopy -O binary bin/kernel.bin bin/kernel.bin

nasm -f bin src/bootloader.asm -o bin/bootloader.bin
cat bin/bootloader.bin bin/kernel.bin > lumin.img

qemu-system-x86_64 -fda lumin.img
