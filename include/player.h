/* player.h */

#ifndef __PLAYER_H__
#define __PLAYER_H__


//! The PlayerState enum
/*!
	A list of states a player object may have.
*/
typedef enum{
	PlayerStateAlive,
	PlayerStateDead
} PlayerState;

//! The Player  structure
/*!
	A Player object represents the current character in game.
*/
typedef struct _Player {
	char name[256];
	int level;
	int experience;
	int health;
	int pos_x;
	int pos_y;
	int move_count;
	PlayerState state;
} Player;

#endif
