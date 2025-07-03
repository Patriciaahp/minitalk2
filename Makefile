NAME_CLIENT = client
NAME_SERVER = server

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

FILES_CLIENT = client.c
FILES_SERVER = server.c

OBJS_CLIENT = $(FILES_CLIENT:.c=.o)
OBJS_SERVER = $(FILES_SERVER:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re