OBJECTS = main.o push.o pop.o peek.o print.o stackSize.o options.o deleteStack.o

.PHONY: clean help

main.exe: $(OBJECTS)
	gcc $(OBJECTS) -o main.exe

%.o: %.c
	gcc -c $<

clean:
	rm -f $(OBJECTS) main.exe

