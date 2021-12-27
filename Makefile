# ***********************************

NAME		= minirt
includes	= ./includes ./lib/libft ./lib/libex ./lib/libvect
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=$(src_dir)/%.o)
obj_bonus	= $(src_bonus:%.c=$(src_dir)/%.o)
BONUS_FLG	= .bonus_flg

# ***********************************

CC			= gcc
LIBS		= -L./lib/libft -L./lib/libex -L./lib/libvect -lft -lex -lvect
CFLAGS		= -Wall -Wextra -Werror -O3 -g $(includes:%=-I%)

# ***********************************

src =\
	./utils2.c \
	./convert_objs.c \
	./init.c \
	./minirt.c \
	./objects2.c \
	./convert_util.c \
	./utils.c \
	./light.c \
	./convert_data.c \
	./bmp.c \
	./objects.c \
	./window.c \

# ***********************************

uname := $(shell uname)
ifeq ($(uname),Darwin)
	mlx_dir = ./lib/minilibx-linux
	mlx_name = libmlx_Darwin.a
	flags += -L $(mlx_dir) -L/usr/X11R6/lib -lmlx -lX11 -lXext -framework OpenGL -framework AppKit
	CFLAGS += -I$(mlx_dir)
endif
ifeq ($(uname),Linux)
	mlx_dir = ./lib/minilibx-linux
	mlx_name = libmlx.a
	flags += -L $(mlx_dir) -lmlx -lX11 -lXext -lm
	CFLAGS += -I$(mlx_dir)
endif

# ***********************************

lib_dir		= lib
lib			= $(libft) \
			$(libex) \
			$(libvect) \
			$(mlx_dir)/$(mlx_name) \

sharedlib	= ./tests/sharedlib.c

# ****************

libft_dir	= $(lib_dir)/libft
libft		= $(libft_dir)/libft.a

# ****************

libex_dir	= $(lib_dir)/libex
libex		= $(libex_dir)/libex.a

# ****************

libvect_dir	= $(lib_dir)/libvect
libvect		= $(libvect_dir)/libvect.a

# ***********************************

.PHONY: all
all					: $(NAME)

$(NAME)				: $(obj) $(lib)
	cp $(mlx_dir)/$(mlx_name) .
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(LIBS) $(flags)
	@$(RM) $(BONUS_FLG)

.PHONY: bonus
bonus			: $(BONUS_FLG)

$(BONUS_FLG)	: $(obj_bonus) $(lib)
	$(CC) $(CFLAGS) $(obj_bonus) -o $(NAME) $(LIBS)
	@touch $(BONUS_FLG)

.PHONY: clean
clean			: lib_clean
	$(RM) $(obj)
	$(RM) -r $(NAME).dSYM
	$(RM) leaksout
	$(RM) $(obj) $(depends) libmlx_Darwin.a libmlx.a libmlx.dylib

.PHONY: fclean
fclean			: clean lib_fclean
	$(RM) $(obj)
	$(RM) $(NAME)
	@$(RM) $(BONUS_FLG)

.PHONY: re
re			: fclean all

# ***********************************

.PHONY: init
init		:
	zsh header.sh $(src_dir) includes/minirt.h Makefile $(src_dir)

.PHONY: sani-debug
sani-debug	: fclean lib_sani-debug
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address" $(lib)
	$(MAKE) clean

# ***********************************

.PHONY: $(libft)
$(libft): $(libft_dir)/*.c
	$(MAKE) -C $(libft_dir)

.PHONY: $(libex)
$(libex): $(libex_dir)/*.c
	$(MAKE) -C $(libex_dir)

.PHONY: $(libvect)
$(libvect): $(libvect_dir)/*.c
	$(MAKE) -C $(libvect_dir)

.PHONY: $(mlx_dir)/$(mlx_name)
$(mlx_dir)/$(mlx_name): $(mlx_dir)/*.c
	$(MAKE) -C $(mlx_dir)

.PHONY: $(lib_make)
lib_make	:$(libft) $(libex) $(libvect) $(mlx_dir)/$(mlx_name)

.PHONY: $(lib_clean)
lib_clean	:
	$(MAKE) clean -C $(libft_dir)
	$(MAKE) clean -C $(libex_dir)
	$(MAKE) clean -C $(libvect_dir)
	$(RM) $(obj) $(depends) libmlx_Darwin.a libmlx.a libmlx.dylib

.PHONY: $(lib_fclean)
lib_fclean	:
	$(MAKE) fclean -C $(libft_dir)
	$(MAKE) fclean -C $(libex_dir)
	$(MAKE) fclean -C $(libvect_dir)
	$(MAKE) clean -C $(mlx_dir)

.PHONY: $(lib_sani-debug)
lib_sani-debug	:
	$(MAKE) -C $(libft_dir)
	$(MAKE) sani-debug -C $(libex_dir)
	$(MAKE) sani-debug -C $(libvect_dir)

FORCE:

# Colors
# ****************************************************************************

_GREY	= \033[30m
_RED	= \033[31m
_GREEN	= \033[32m
_YELLOW	= \033[33m
_BLUE	= \033[34m
_PURPLE	= \033[35m
_CYAN	= \033[36m
_WHITE	= \033[37m
_END	= \033[0m
