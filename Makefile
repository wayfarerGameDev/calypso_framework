# Shared
CC = gcc
CC_FLAGS_DEBUG = -std=c99 -Wall -O0 -g
CC_FLAGS_RELEASE = -std=c99 -O3
LIBRARY_PATH_32 = -Idependencies/32/Include -Ldependencies/32/lib
LINKER_FLAGS_32 = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
LIBRARY_PATH_64 = -Idependencies/64/Include -Ldependencies/64/lib
LINKER_FLAGS_64 = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Shared Win
clear_console_win:
	cls

# Win 32
BUILD_DIR_DEBUG_32_WIN = build/debug_32_win/app
RUN_DIR_DEBUG_32_WIN = ./build/debug_32_win/app
RUN_DIR_RELEASE_32_WIN = ./build/release_32_win/app
BUILD_DIR_RELEASE_32_WIN = build/release_32_win/app

build_debug_32_win: clear_console_win
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH_32) -o $(BUILD_DIR_DEBUG_32_WIN) src/game_main.c $(LINKER_FLAGS_32)
build_release_32_win: clear_console_win
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH_32) -o $(BUILD_DIR_RELEASE_32_WIN) src/game_main.c $(LINKER_FLAGS_32)
run_debug_32_win: clear_console_win
	$(RUN_DIR_DEBUG_32_WIN)
run_release_32_win: clear_console_win
	$(RUN_DIR_RELEASE_32_WIN)

# Win 64
BUILD_DIR_DEBUG_64_WIN = build/debug_64_win/app
RUN_DIR_DEBUG_64_WIN = ./build/debug_64_win/app
RUN_DIR_RELEASE_64_WIN = ./build/release_64_win/app
BUILD_DIR_RELEASE_64_WIN = build/release_64_win/app

build_debug_64_win: clear_console_win
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH_64) -o $(BUILD_DIR_DEBUG_64_WIN) src/game_main.c $(LINKER_FLAGS_64)
build_release_64_win: clear_console_win
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH_64) -o $(BUILD_DIR_RELEASE_64_WIN) src/game_main.c $(LINKER_FLAGS_64)
run_debug_64_win: clear_console_win
	$(RUN_DIR_DEBUG_64_WIN)
run_release_64_win: clear_console_win
	$(RUN_DIR_RELEASE_64_WIN)