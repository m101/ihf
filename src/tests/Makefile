TEST_EXPLODE = test_explode
TEST_B64 = test_b64
CFLAGS 	=	-g -Wall -std=c99
LDFLAGS	=

all: $(TEST_EXPLODE)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) -I../

$(TEST_EXPLODE): test_explode.o ../libihf.o
	$(CC) test_explode.o ../libihf.o -o $(TEST_EXPLODE) $(LDFLAGS) $(CFLAGS) -I../

$(TEST_B64): test_base64.o ../base64.o
	$(CC) test_base64.o ../base64.o -o $(TEST_B64) $(LDFLAGS) $(CFLAGS) -I../

.PHONY: clean mrproper

mrproper: clean

clean:
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) *~ *.o

