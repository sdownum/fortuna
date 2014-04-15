/* game_state.h */

#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <wchar.h>
#include <unistd.h>
#include <time.h>

#include "player.h"

// Game Function Return Codes
typedef int FSTATUS;


//! The GameState structure
/*!
	A GameState object is a table that represents the current game. It is the
	primary data store for a Fortuna session.
*/
typedef struct _GameState {
	int isNewGame;
	time_t start_time;
	time_t end_time;
	char* user;
	char savefile[1024];
	Player player;
} GameState;


FSTATUS new_game(GameState *state);
FSTATUS get_game_state(GameState *state);
FSTATUS save_game_state(GameState *state, wchar_t *filename);



#endif
