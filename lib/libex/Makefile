# ***********************************

NAME	= libex.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3 -g
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./free_ss.c \
	./ft_free_return.c \
	./ft_get_next_line.c \
	./ft_isprintable.c \
	./ft_isspace.c \
	./ft_split_charset.c \
	./ft_strcmp.c \
	./ft_strndup.c \
	./ft_strrncmp.c \
	./is_n_char.c \
	./is_n_split.c \
	./is_ranges.c \

# ***********************************

all: $(NAME)

$(NAME): $(obj)
	$(AR) -rc $(NAME) $(obj)
	ranlib $(NAME)

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ***********************************

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address"

init:
	bash header.sh libex.h Makefile
