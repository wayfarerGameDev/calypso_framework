debug:
	gcc -Isrc/Include -Lsrc/lib -o app_debug src/game_main.c -lmingw32 -lSDL2main -lSDL2