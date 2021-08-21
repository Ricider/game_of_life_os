#ifndef VGA_H
#define VGA_H

#define VGA_ADRESS 0xb8000

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

#define TEXT_COLOR 0xa0
#define MAX_ROWS 25
#define MAX_COLUMNS 80

void set_cursor(int offset);
int get_cursor();
void set_char_at_video_memory(char character, int offset);

#endif // !VGA_H