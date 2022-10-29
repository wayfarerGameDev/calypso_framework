CC = gcc
CC_FLAGS_DEBUG = -std=c99 -Wall -O0 -g
CC_FLAGS_RELEASE = -std=c99 -O3
BUILD_DIR_DEBUG_32 = build/debug_32/app
RUN_DIR_DEBUG_32 = ./build/debug_32/app
RUN_DIR_RELEASE_32 = ./build/release_32/app
BUILD_DIR_RELEASE_32 = build/release_32/app
LIBRARY_PATH_32 = -Idependencies/32/Include -Ldependencies/32/lib
LINKER_FLAGS_32 = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

clear_console:
	cls

build_debug_32: clear_console
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH_32) -o $(BUILD_DIR_DEBUG_32) src/game_main.c $(LINKER_FLAGS_32)

build_release_32: clear_console
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH_32) -o $(BUILD_DIR_RELEASE_32) src/game_main.c $(LINKER_FLAGS_32)

run_debug_32: clear_console
	$(RUN_DIR_DEBUG_32)

run_release_32: clear_console
	$(RUN_DIR_RELEASE_32)