/* map.h */

#ifndef __MAP_H__
#define __MAP_H__


// Default start position on map
#define PLAYER_START_X 40
#define PLAYER_START_Y 12


//! The Map structure
/*!
	A Map object represents the current level in game.
*/

typedef struct _Map {
	int xstart;
	int ystart;
	int len;
	int rows;
}Map;


//! The gen_map function
/*!
	A function to create a random map for a game level.
*/
void gen_map(Map map);

//! The lookup_location function
/*!
	A function to report what the player is standing on.
*/
char lookup_location(int loc);

#endif
