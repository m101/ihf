CFLAGS+=-Wall
LDFLAGS=

all:
	make srv
	make cli

cli:

srv:
	make lib
	$(CC) srv.o lib.o -o srv $(LDFLAGS)

lib:
	$(CC) libihf.c -o libihf.o

clean:
	rm -f $(PROG) *~ *.o

