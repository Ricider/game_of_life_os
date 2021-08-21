#include "port_io.h"
#include "vga.h"

void set_cursor(int offset) {
	offset /= 2;
	port_output(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
	port_output(VGA_DATA_REGISTER, (unsigned char)(offset >> 8));
	port_output(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
	port_output(VGA_DATA_REGISTER, (unsigned char)(offset & 0xff));
}

int get_cursor() {
	port_output(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
	int offset = port_input(VGA_DATA_REGISTER) << 8;
	port_output(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
	offset += port_input(VGA_DATA_REGISTER);
	return offset * 2;
}

void set_char_at_video_memory(char character, int offset) {
	unsigned char* vidmem = (unsigned char*)VGA_ADRESS;
	vidmem[offset] = character;
	vidmem[offset + 1] = TEXT_COLOR;
}