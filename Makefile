#Simple makefile template

COM = clang #Compiler to be used
OBJS = main.c entities.c globals.c input.c utilities.c  #Objects to be compiled (.c)
COM_FLAGS = -O2 -march=native -fomit-frame-pointer -std=c11 -Wall -pedantic #Compiler flags
INC_DIRS = -I/usr/include/SDL2 
LNK_FLAGS = -lSDL2 -lSDL2main -lSDL2_image -lm #Linker flags
EXE = PROGRAM #Name of the final executable

all: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(INC_DIRS) $(LNK_FLAGS) -o $(EXE)

main: main.c
	$(COM) $(COM_FLAGS) -c main.c

entities: entities.c
	$(COM) $(COM_FLAGS) -c entities.c
	
globals: globals.c
	$(COM) $(COM_FLAGS) -c globals.c
	
input: input.c
	$(COM) $(COM_FLAGS) -c input.c

clean:
	rm -f $(EXE) *.o
