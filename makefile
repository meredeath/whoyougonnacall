all: client server

server: main_server.o networking.o bsearch.o
	gcc -o server main_server.o networking.o bsearch.o

main_server.o: main_server.c networking.h bsearch.h main_server.h
	gcc -c main_server.c

client: client.o networking.o
	gcc -o client client.o networking.o

client.o: client.c networking.h
	gcc -c client.c

bsearch.o: bsearch.c bsearch.h
	gcc -c bsearch.c

networking.o: networking.c networking.h
	gcc -c networking.c

clientmethods.o: clientmethods.c networking.h
	gcc -c clientmethods.c

clean:
	rm *.o
	rm *~
