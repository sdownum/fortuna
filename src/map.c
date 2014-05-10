#include <ncurses.h>

#include "map.h"

char location[256];

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

	// add a test item - the datapad
	location[map.len - 1 - map.rows] = '#';
	mvaddch(map.ystart-1, orig_x, '#');
}

char lookup_location(int loc) {
	if (loc > 256 || loc < 1)
		return ' ';
	return location[loc];
}
