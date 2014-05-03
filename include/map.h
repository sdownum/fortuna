/* map.h */

#ifndef __MAP_H__
#define __MAP_H__


// Default start position on map
#define PLAYER_START_X 40
#define PLAYER_START_Y 12

//! The gen_map function
/*!
	A function to create a random map for a game level.
*/
void gen_map(int x, int y, int size, int width);
#endif
