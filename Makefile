# Shared
# MAIN_FILE = source/example_engine_sdl/example_engine_sdl_editor.c
MAIN_FILE = source/testbeds/testbed_renderer_opengl_es.c
CC = gcc
CC_FLAGS_DEBUG = -std=c99 -Wall -O0 -g -DNDEBUG
CC_FLAGS_RELEASE = -std=c99 -O3
LIBRARY_PATH_32 = -Idependencies/sdl2_32/Include -Ldependencies/sdl2_32/lib -Idependencies/glad/include
LINKER_FLAGS_32 = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -m64
LIBRARY_PATH_64 = -Idependencies/sdl2_64/Include -Ldependencies/sdl2_64/lib -Idependencies/glad/include -Idependencies/glfw_64/include -Ldependencies/glfw_64/lib
LINKER_FLAGS_64 = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lglfw3 -lgdi32  -m64 #-lgdi32 needed for glfw3 
SOURCE_FILES =  $(MAIN_FILE) dependencies/glad/source/glad.c

# Shared Win
clear_console_win:
	cls

# Win 32
BUILD_DIR_DEBUG_WIN_32 = build/debug_win_32/app
RUN_DIR_DEBUG_WIN_32 = ./build/debug_win_32/app
BUILD_DIR_RELEASE_WIN_32 = build/release_win_32/app
RUN_DIR_RELEASE_WIN_32 = ./build/release_win_32/app

build_debug_win_32: clear_console_win
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH_32) -o $(BUILD_DIR_DEBUG_WIN_32) $(SOURCE_FILES) $(LINKER_FLAGS_32)
build_release_win_32: clear_console_win
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH_32) -o $(BUILD_DIR_RELEASE_WIN_32) $(SOURCE_FILES) $(LINKER_FLAGS_32)
run_debug_win_32: clear_console_win
	$(RUN_DIR_DEBUG_WIN_32)
run_release_win_32: clear_console_win
	$(RUN_DIR_RELEASE_WIN_32)

# Win 64
BUILD_DIR_DEBUG_WIN_64 = build/debug_win_64/app
RUN_DIR_DEBUG_WIN_64 = ./build/debug_win_64/app
BUILD_DIR_RELEASE_WIN_64 = build/release_win_64/app
RUN_DIR_RELEASE_WIN_64 = ./build/release_win_64/app

build_debug_win_64: clear_console_win
	$(CC) $(CC_FLAGS_DEBUG) $(LIBRARY_PATH_64) -o $(BUILD_DIR_DEBUG_WIN_64) $(SOURCE_FILES) $(LINKER_FLAGS_64)
build_release_win_64: clear_console_win
	$(CC) $(CC_FLAGS_RELEASE) $(LIBRARY_PATH_64) -o $(BUILD_DIR_RELEASE_WIN_64) $(SOURCE_FILES) $(LINKER_FLAGS_64)
run_debug_win_64: clear_console_win
	$(RUN_DIR_DEBUG_WIN_64)
run_release_win_64: clear_console_win
	$(RUN_DIR_RELEASE_WIN_64)