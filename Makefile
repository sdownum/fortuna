fortuna: fortuna.o game_state.o map.o
	clang -I ./include -lncurses -o fortuna fortuna.o game_state.o map.o

game_state.o: src/game_state.c
	clang -I ./include -c src/game_state.c 

map.o: src/map.c
	clang -I ./include -c src/map.c 

fortuna.o: src/fortuna.c
	clang -I ./include -c src/fortuna.c 

clean:
	rm *.o
	rm fortuna
	rm ~/.fortunarc
