CC = gcc-11
FFLAGS = -Wall -O3 -std=c99 -fopenmp -fopenacc
LFLAGS = -lgomp
OBJECTS = adaptive_int_omp1.o

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe
