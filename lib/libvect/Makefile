# ***********************************

NAME	= libvect.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O2 -g
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./init_vect.c \
	./is_inline.c \
	./is_vinf.c \
	./is_vrange.c \
	./is_vsame.c \
	./is_vzero.c \
	./vadd.c \
	./vcross.c \
	./vdiv.c \
	./vdot.c \
	./vectlen.c \
	./vectlen2.c \
	./vscale.c \
	./vsub.c \
	./vunit.c \

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

init:
	bash header.sh libvect.h Makefile

# ***********************************

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address"
