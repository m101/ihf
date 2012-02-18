TARGET_SERVER = srv
TARGET_CLIENT = cli
CFLAGS 	=	-g -Wall
LDFLAGS	=

all: srv cli

cli:

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(TARGET_SERVER): srv.o libihf.o
	$(CC) srv.o libihf.o -o srv $(LDFLAGS) $(CFLAGS)

.PHONY: clean mrproper

mrproper: clean

clean:
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) *~ *.o

