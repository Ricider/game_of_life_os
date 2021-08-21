#include "screen.h"
#include "vga.h"

#define CALC_POS(y,x) ((y)*MAX_COLUMNS+(x))

enum state {dead=0,alive=1};

enum state frame_1[MAX_COLUMNS * MAX_ROWS];
enum state frame_2[MAX_COLUMNS * MAX_ROWS];

enum state *current_frame;
enum state *buffer_frame;

int calculate_neighbors(int x,int y)
{
	char i,j,neighbor_count = 0;
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			if (
				(i==0 && j==0) ||
				(x+i<0) ||
				(y+j<0) ||
				(x + i >= MAX_COLUMNS) ||
				(y + j >= MAX_ROWS)
				) continue;
			if (current_frame[CALC_POS(y + j, x + i)] == alive)
				neighbor_count++;
		}
	}
	return neighbor_count;
}

void advance_frame()
{
	unsigned char x, y, neighbor_count;
	for (y = 0; y < MAX_ROWS; y++)
	{
		for (x = 0; x < MAX_COLUMNS; x++)
		{
			neighbor_count = calculate_neighbors(x, y);
			enum state cell_state = current_frame[CALC_POS(y, x)];
			if (cell_state == alive && (neighbor_count == 2 || neighbor_count == 3))
				buffer_frame[CALC_POS(y,x)] = alive;
			else if (cell_state == dead && neighbor_count == 3)
				buffer_frame[CALC_POS(y, x)] = alive;
			else 
				buffer_frame[CALC_POS(y, x)] = dead;
		}
	}
	
	enum state* temp = current_frame;
	current_frame = buffer_frame;
	buffer_frame = temp;
}

void draw_frame()
{
	unsigned char x, y;
	clear_screen();
	for (y = 0; y < MAX_ROWS; y++)
	{
		for (x = 0; x < MAX_COLUMNS; x++)
		{
			enum state cell_state = current_frame[CALC_POS(y, x)];
			if (cell_state == alive) put_dot(y, x);
		}
	}
}

void main() {
	clear_screen();

	current_frame = &frame_1[0];
	buffer_frame = &frame_2[0];

	current_frame[CALC_POS(20,5)] = alive;
	current_frame[CALC_POS(20,6)] = alive;
	current_frame[CALC_POS(20,7)] = alive;

	while (1)
	{
		advance_frame();
		draw_frame();
	}
}