CC = gcc
CC_FLAGS_DEBUG = -std=c99 -Wall -O0 -g
CC_FLAGS_RELEASE = -std=c99 -O3
BUILD_DIR_DEBUG = build/debug/app
BUILD_DIR_RELEASE = build/release/app
LIBRARY_PATH = -Isrc/Include -Lsrc/lib
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

clear_console:
	cls

build_debug: clear_console
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH) -o $(BUILD_DIR_DEBUG) src/game_main.c $(LINKER_FLAGS)

build_release: clear_console
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH) -o $(BUILD_DIR_RELEASE) src/game_main.c $(LINKER_FLAGS)

run_debug: clear_console
	./build/debug/app

run_release: clear_console
	./build/release/app
