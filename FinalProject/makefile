CC = mpicc
FFAGS = -03 -Wall -std=c99
LFLAGS = 
OBJECTS = main.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm -o main.exe

%.o: %c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f *.o *.exe
