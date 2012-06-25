tcpserver: tcpserver.o io.o
	gcc -o tcpserver tcpserver.o io.o -Wall

tcpserver.o: tcpserver.c io.h
	gcc -o tcpserver.o tcpserver.c -c -ansi -pedantic -Wall

io.o: io.c io.h
	gcc -o io.o io.c -c -ansi -pedantic -Wall

