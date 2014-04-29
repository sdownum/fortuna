#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <ncurses.h>

#include "fortuna.h"

int main(int argc, char* argv[])
{

	GameState game;
	int dbg_game;

	dbg_game = get_game_state(&game);

	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	nonl(); intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	waddwstr(stdscr, L"Welcome to Fortuna - Version 0.1\n");
	waddwstr(stdscr, L"Build 4, 22 Apr 2014\n\n");
	waddwstr(stdscr, L"Welcome, ");
	waddstr(stdscr, game.user);
	waddwstr(stdscr, L"!\n");
	gen_map(39, 11, 15, 5);
	mvaddch(12, 40, '@');
	mvaddch(20, 0, '\n');

	if (game.player.state == PlayerStateDead) {
		mvaddch(12, 40, 'X');
		mvaddch(20, 0, '\n');
		waddstr(stdscr, game.user);
		waddwstr(stdscr, L" has died.\n\n");
		new_game(&game);
	} else {
		start_game(&game);
	}

	waddwstr(stdscr, L"Press a key to exit.\n");
	getch();

	endwin();

	wprintf(L"Good-bye. We'll see you again soon.\n");

	return EXIT_SUCCESS;
}
