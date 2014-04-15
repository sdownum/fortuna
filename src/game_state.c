/* game_state.c */

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "game_state.h"

//! Creates a new game.
/*!
	This function initializes a GameState object to set up a new game.
*/
FSTATUS new_game(GameState *state) 
{
	Player p;
	int fd;
	ssize_t b_written;	

	state->user = getlogin();
	state->start_time = time(NULL);
	state->end_time = 0;

	p.level = 1;
	p.experience = 0;
	strncpy(p.name, state->user, 255);	

	state->player = p;
	
	struct passwd *pw;
	pw = getpwnam(state->user);
	strncpy(state->savefile, pw->pw_dir, 1000);
	strncat(state->savefile, "/.forunarc", 10);

	// Create a stub save file
	fd = open(state->savefile, O_WRONLY | O_CREAT, 0700);

	if (fd < 0)
		return 1;
	
	b_written = write(fd, "fortuna", 7); 
	
	if (b_written < 0)
		return 2;	

	close(fd);

	return 0;
}

FSTATUS get_game_state(GameState *state);
FSTATUS save_game_state(GameState *state, wchar_t *filename);
