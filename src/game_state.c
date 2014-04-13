/* game_state.c */



#include "game_state.h"

//! Creates a new game.
/*!
	This function initializes a GameState object to set up a new game.
*/
FSTATUS new_game(GameState *state) 
{
	state->user = getlogin();
	state->start_time = time(NULL);
	state->end_time = 0;
	return 0;
}

FSTATUS get_game_state(GameState *state);
FSTATUS save_game_state(GameState *state, wchar_t *filename);
