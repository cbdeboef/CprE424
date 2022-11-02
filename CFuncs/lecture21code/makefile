CC = mpicc
FFLAGS = -O3 -Wall -std=c99
LFLAGS =
OBJECTS = main.o vector.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe
