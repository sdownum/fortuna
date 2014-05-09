/* game_state.c */

#include <sys/types.h>
#include <sys/uio.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>

#include "game_state.h"

#define PLAYER_START_X 40
#define PLAYER_START_Y 12

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
	p.move_count = 0;
	p.state = PlayerStateAlive;
	p.pos_x = PLAYER_START_X;
	p.pos_y = PLAYER_START_Y;
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
}

void start_game(GameState *state)
{
	Map map;
	int player_x = 40;
	int player_y = 12;
	int info_x = 0;
	int info_y = 20;
	char buf[256];

	map.xstart = 39;
	map.ystart = 11;
	map.len = 25;
	map.rows = 5;

	gen_map(map);
	mvaddch(state->player.pos_y, state->player.pos_x, '@');
	mvaddstr(info_y -1, info_x, state->player.name);
	waddstr(stdscr, " the Android\t");
	waddstr(stdscr, "Level: ");
	sprintf(buf, "%d", state->player.level);
	waddstr(stdscr, buf);	
	waddstr(stdscr, "\tHealth: ");
	sprintf(buf, "%d", state->player.health);
	waddstr(stdscr, buf);	
	waddstr(stdscr, "\tArea: Testing Lab");
	mvaddch(info_y, info_x, '\n');

	if (state->player.state == PlayerStateDead) {
		mvaddch(state->player.pos_y, state->player.pos_x, 'X');
		mvaddch(info_y, info_x, '\n');
		waddstr(stdscr, state->user);
		waddwstr(stdscr, L" has died.\n");
		sprintf(buf, "Number of moves: %d\n", state->player.move_count);
		waddstr(stdscr, buf);
		new_game(state);
		return;
	}

	// game loop
	while(state->player.state != PlayerStateDead) {
		char move = ' ';
		while (move != 'q') {
			waddstr(stdscr, "Move: ");
			waddch(stdscr, move);
			move = getch();
			state->player.move_count++;
			switch (move) {
				case 'a':
					if (state->player.pos_x - 1 >= map.xstart)
						state->player.pos_x--;
					break;;
				case 'w':
					if (state->player.pos_y - 1 >= map.ystart)
						state->player.pos_y--;
					break;;
				case 's':
					if (state->player.pos_y + 1 < map.ystart + (map.len/map.rows))
						state->player.pos_y++;
					break;;
				case 'd':
					if (state->player.pos_x + 1 < map.xstart + map.rows)
						state->player.pos_x++;
					break;;
				case 'A':
						state->player.state = PlayerStateDead;
						state->player.health = 0;	
						waddstr(stdscr, "\n");
						mvaddstr(0, 40, "Abandoning game...");
						move = 'q';;		
					break;;
				default:
					state->player.move_count--;
					break;;
			}
		 	gen_map(map);
			mvaddch(state->player.pos_y, state->player.pos_x, '@');
			mvaddch(info_y, info_x, '\n');
		}
		waddstr(stdscr, "\n");
		save_game_state(state);
		break;
	}

	return; 
}
