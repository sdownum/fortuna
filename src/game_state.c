/* game_state.c */


#include <string.h>


#include "game_state.h"

//! Creates a new game.
/*!
	This function initializes a GameState object to set up a new game.
*/
FSTATUS new_game(GameState *state) 
{
	Player p;

	state->user = getlogin();
	state->start_time = time(NULL);
	state->end_time = 0;

	p.level = 1;
	p.experience = 0;
	strncpy(p.name, state->user, 255);	

	state->player = p;

	return 0;
}

FSTATUS get_game_state(GameState *state);
FSTATUS save_game_state(GameState *state, wchar_t *filename);
