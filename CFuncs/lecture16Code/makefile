CC = gcc-11
FFLAGS = -Wall -O3 -std=c99 -fopenmp
LFLAGS = -lgomp
OBJECTS = forloop.o matrix.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe
