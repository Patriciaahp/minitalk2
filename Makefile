CC = gcc

CFLAGS = -Wall -Wextra -Werror

TARGETS = server client

all: $(TARGETS)

server: server.o
	$(CC) $(CFLAGS) -o server server.o

client: client.o
	$(CC) $(CFLAGS) -o client client.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f *.o $(TARGETS)