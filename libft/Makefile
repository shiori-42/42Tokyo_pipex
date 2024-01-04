NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I. -I./ft_printf -I./get_next_line

SRCS= ft_isdigit.c \
ft_memset.c ft_strdup.c ft_strncmp.c \
ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c \
ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c \
ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c \
ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c \
ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c	ft_tolower.c \
ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c

SRCS_BONUS=ft_lstnew_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c \
ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c \
ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c \

OBJS = $(SRCS:.c=.o)

PRINTF_SRC = ft_printf/ft_itoa_base.c ft_printf/ft_itoa_base_ptr.c \
ft_printf/ft_printf.c ft_printf/handle_c.c \
ft_printf/handle_d_or_i.c ft_printf/handle_lowhex.c \
ft_printf/handle_p.c ft_printf/handle_percent_symbol.c \
ft_printf/handle_s.c ft_printf/handle_u.c \
ft_printf/handle_upperhex.c

PRINTF_OBJ = $(PRINTF_SRC:.c=.o)

GNL_SRC = get_next_line/get_next_line.c
GNL_OBJ = $(GNL_SRC:.c=.o)

ALL_OBJ = $(OBJS) $(PRINTF_OBJ) $(GNL_OBJ)

ifdef WITH_BONUS
OBJS+=$(SRCS_BONUS:.c=.o)
endif

all: $(NAME)

$(NAME): $(ALL_OBJ)
	ar rc $(NAME) $(ALL_OBJ)
	ranlib $(NAME)

bonus:
	make WITH_BONUS=1 all

%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(ALL_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus