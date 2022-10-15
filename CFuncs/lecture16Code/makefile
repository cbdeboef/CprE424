CC = gcc
FFLAGS = -O3 -Wall -std=c99 -c
LFLAG = -lm
OBJECTS = QRtimed.o FindZero.o GetShift.o Hessenberg.o matrix.o QRA.o QRdecomp.o trimatrix.o

.PHONY: clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe output.txt