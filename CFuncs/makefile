OBJECTS = main.o quad_perimeter.o quad_area.o quad_angle.o

output.txt: main.exe
	./main.exe > output.txt

main.exe: $(OBJECTS)
	gcc $(OBJECTS) -o main.exe

%.o: %.c
	gcc -c $<
