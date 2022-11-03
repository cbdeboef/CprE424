CC = mpicc
FFLAGS = -O3 -Wall -std=c99
LFLAGS = -lm
OBJECTS = main.o

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe
