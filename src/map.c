#include <ncurses.h>

#include "map.h"

void gen_map(Map map)
{
	int orig_x = map.xstart;
	int x_len = 1;

	for (int i = 0; i < map.len; i++)
	{
		mvaddch(map.ystart, map.xstart, '.');

		if (x_len == map.rows) {
			map.xstart = orig_x;
			x_len = 1;
			map.ystart++;
		} else {
			map.xstart++;
			x_len++;
		}
	}
}
