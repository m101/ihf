CFLAGS 	=	-g -Wall
LDFLAGS	=

all: srv cli

cli:

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

srv: srv.o libihf.o
	$(CC) srv.o libihf.o -o srv $(LDFLAGS) $(CFLAGS)

.PHONY: clean mrproper

mrproper: clean

clean:
	rm -f $(PROG) *~ *.o

