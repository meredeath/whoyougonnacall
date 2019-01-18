all: client server

setup:
	gcc makedict.c
	./a.out

delete:
	ipcrm -m 1245184

test:
	gcc test.c bsearch.c bsearch.h

server: main_server.o networking.o bsearch.o
	gcc -o server main_server.o networking.o bsearch.o

main_server.o: main_server.c networking.h bsearch.h main_server.h
	gcc -c -g main_server.c

client: client.o networking.o clientmethods.o
	gcc -o client client.o networking.o clientmethods.o

client.o: client.c networking.h
	gcc -c -g client.c

bsearch.o: bsearch.c bsearch.h
	gcc -c -g bsearch.c

networking.o: networking.c networking.h
	gcc -c -g networking.c

clientmethods.o: clientmethods.c networking.h
	gcc -c -g clientmethods.c

clean:
	rm *.o
	rm *~
