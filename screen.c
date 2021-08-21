#include "screen.h"
#include "vga.h"

#define POS(x,y) (2*(y)*MAX_COLUMNS + (x)*2)

void print_string(char* string) {
	int offset = get_cursor();
	int i = 0;
	while (string[i] != 0) {
		set_char_at_video_memory(string[i], offset);
		i++;
		offset += 2;
	}
	set_cursor(offset);
}

void put_dot(int x, int y) {
	unsigned char* vidmem = (unsigned char*)VGA_ADRESS;
	vidmem[POS(x,y)] = ' ';
	vidmem[POS(x,y) + 1] = 0x22;
}

void clear_screen()
{
	unsigned char* vidmem = (unsigned char*)VGA_ADRESS;
	int i;
	for (i = 0; i < MAX_COLUMNS * MAX_ROWS * 2; i++)
	{
		vidmem[i]=0;
	}
}