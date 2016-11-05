ser:	ser.o cli.o
	gcc -o ser ser.o
	gcc -o cli cli.o
ser.o:	ser.c cli.o
	gcc -c ser.c
	gcc -c cli.c
clean:
	rm *.o
