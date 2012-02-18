TARGET_SERVER = srv
TARGET_CLIENT = cli
CFLAGS 	=	-g -Wall
LDFLAGS	=

all: $(TARGET_CLIENT) $(TARGET_SERVER)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(TARGET_SERVER): srv.o libihf.o
	$(CC) srv.o libihf.o -o $(TARGET_SERVER) $(LDFLAGS) $(CFLAGS)

$(TARGET_CLIENT): cli.o libihf.o
	$(CC) cli.o libihf.o -o $(TARGET_CLIENT) $(LDFLAGS) $(CFLAGS)

.PHONY: clean mrproper

mrproper: clean

clean:
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) *~ *.o

