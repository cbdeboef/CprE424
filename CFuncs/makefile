output.txt: main.exe
	./main.exe > output.txt

main.exe: main.o quad_perimeter.o quad_area.o quad_angle.o -o main.exe

main.o: main.c
	gcc -c main.c
quad_perimeter.o: quad_perimeter.c
	gcc -c quad_perimeter.c
quad_area.o: quad_area.c
	gcc -c quad_area.c
quad_angle.o: quad_angle.c
	gcc -c quad_angle.c
