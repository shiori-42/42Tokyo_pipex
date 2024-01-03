CC=cc
CFLAGS=-Wall -Wextra -Werror

LIBFT=libft/libft.a
SRCFILES=main.c utils.c pipe.c

OBJS=$(SRCFILES:.c=.o)

NAME=pipex

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -I. -I./libft  -o $(NAME) $(OBJS) -L ./libft -lft

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I. -I./libft -c $< -o $@

clean: 	
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

