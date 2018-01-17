#Simple makefile template

COM = gcc #Compiler to be used (gcc, g++, clang, clang++, etc.)

OBJS = main.c entities.c globals.c input.c utilities.c map.c #Objects to be compiled (.c or .cpp files)

COM_FLAGS = -O2 -march=native -fomit-frame-pointer -std=c11 -Wall -pedantic #Compiler flags

WIN_MINGW_PATH = C:/msys64/mingw64


INC_DIRS = -I/usr/include/SDL2 #Include directories

WIN_INC_DIRS = -I$(WIN_MINGW_PATH)/include/SDL2 #Include directories for Windows
WIN_LIB_DIRS = -L$(WIN_MINGW_PATH)/lib/libxml2 #Library directories for Windows

LNK_FLAGS     = -lSDL2main -lSDL2 -lSDL2_image -lm -ltmx -lz -lxml2  #Linker flags
WIN_LNK_FLAGS = -Dmain=SDL_main -mconsole -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm -ltmx -lz -lxml2  #Linker flags for Windows

EXE = PROGRAM


all: $(OBJS)
	$(COM) -o $(EXE) $(OBJS) $(WIN_INC_DIRS) $(WIN_LNK_FLAGS)

#Microsoft WinHell
win: $(OBJS)
	$(COM) -o $(EXE) $(OBJS) $(WIN_INC_DIRS) $(WIN_LNK_FLAGS)

clean:
	rm -f $(EXE) *.o *.swp .*.swp
