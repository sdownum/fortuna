/* game_state.c */

#include <sys/types.h>
#include <sys/uio.h>
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

	strncpy(state->user, getlogin(), 1024);
	state->start_time = time(NULL);
	state->end_time = 0;

	p.level = 1;
	p.experience = 0;
	p.health = 10;
	p.state = PlayerStateAlive;
	strncpy(p.name, state->user, 255);	

	state->player = p;
	
	struct passwd *pw;
	pw = getpwnam(state->user);
	strncpy(state->savefile, pw->pw_dir, 1000);
	strncat(state->savefile, "/.fortunarc", 11);

	// insert save here
	return save_game_state(state);
}

FSTATUS get_game_state(GameState *state) 
{
	ssize_t b_written;	
	int fd;
	char savefile[1024];
	char user[1024];
	struct passwd *pw;

	strncpy(user, getlogin(), 1024);
	pw = getpwnam(user);
	strncpy(savefile, pw->pw_dir, 1000);
	strncat(savefile, "/.fortunarc", 11);

	// Create a stub save file
	fd = open(savefile, O_RDONLY);

	if (fd < 0)
		return new_game(state);
	
	b_written = read(fd, state, sizeof(GameState)); 
	
	if (b_written < 0)
		return 2;	

	close(fd);

	return 0;
}

FSTATUS save_game_state(GameState *state)
{
	int fd;
	ssize_t b_written;	

	fd = open(state->savefile, O_WRONLY | O_CREAT, 0700);

	if (fd < 0)
		return 1;
	
	b_written = write(fd, state, sizeof(GameState)); 
	
	if (b_written < 0)
		return 2;	

	close(fd);
	return 0;
};

void start_game(GameState *state)
{
	while(state->player.state != PlayerStateDead) {
		state->player.state = PlayerStateDead;
		state->player.health = 0;	
		save_game_state(state);
	}

	return; 
}
