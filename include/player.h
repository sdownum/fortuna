/* player.h */

#ifndef __PLAYER_H__
#define __PLAYER_H__

//! The Player  structure
/*!
	A Player object represents the current character in game.
*/
typedef struct _Player {
	char name[256];
	int level;
	int experience;
} Player;

#endif
