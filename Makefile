all: clean build
	qemu-system-i386 -fda os.bin

build: vga.o port_io.o screen.o 
	gcc -m32 -fno-pie -ffreestanding -c kernel.c -o kernel.o 
	nasm start.s -f elf -o start.o
	nasm boot.s -f bin -o boot.bin
	ld -m elf_i386 -o main.bin -Ttext 0x1000 start.o kernel.o vga.o port_io.o screen.o  --oformat binary
	cat boot.bin main.bin > os.bin
	
vga.o: 
	gcc -m32 -fno-pie -ffreestanding -c vga.c -o vga.o
	
port_io.o: 
	gcc -m32 -fno-pie -ffreestanding -c port_io.c -o port_io.o
	
screen.o: 
	gcc -m32 -fno-pie -ffreestanding -c screen.c -o screen.o
	
clean:
	rm *.o
	rm *.bin