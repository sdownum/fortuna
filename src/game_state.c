/* game_state.c */



#include "game_state.h"

//! Creates a new game.
/*!
	This function initializes a GameState object to set up a new game.
*/
FSTATUS new_game(GameState *state);
FSTATUS get_game_state(GameState *state);
FSTATUS save_game_state(GameState *state, wchar_t *filename);
