CC=g++

OBJ=main.o maze.o path_finder.o

%.o: %.c
	$(CC) -c -o $@ $<
a.exe: $(OBJ)
	$(CC) -o $@ $^