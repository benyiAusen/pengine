#Simple makefile template

COM = gcc #Compiler to be used (gcc, clang, clang++, etc.)
OBJS = main.c entities.c globals.c input.c utilities.c map.c #Objects to be compiled (.c or .cpp files)
COM_FLAGS = -O2 -march=native -fomit-frame-pointer -std=c11 -Wall -pedantic #Compiler flags

WIN_MINGW_PATH = C:/msys64/mingw64

INC_DIRS = -I/usr/include/SDL2 #Include directories
WIN_INC_DIRS = -I$(WIN_MINGW_PATH)/include/SDL2 #Include directories for Windows

LNK_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lm #Linker flags
WIN_LNK_FLAGS = -Dmain=SDL_main -L$(WIN_MINGW_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm -mwindows #Linker flags for Windows

EXE = PROGRAM #Name of the final executable



all: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(INC_DIRS) $(LNK_FLAGS) -o $(EXE)

win: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(WIN_INC_DIRS) $(WIN_LNK_FLAGS) -o $(EXE)

clean:
	rm -f $(EXE) *.o
