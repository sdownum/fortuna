#include <ncurses.h>

#include "map.h"

void gen_map(int x, int y, int size, int width)
{
	int orig_x = x;
	int x_len = 1;

	for (int i = 0; i < size; i++)
	{
		mvaddch(y, x, '.');

		if (x_len == width) {
			x = orig_x;
			x_len = 1;
			y++;
		} else {
			x++;
			x_len++;
		}
	}
}
