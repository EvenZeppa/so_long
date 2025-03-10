CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_FOLDER = ft_lib
LIBFT = $(LIBFT_FOLDER)/libft.a

MLX_FOLDER = minilibx-linux
MLX = $(MLX_FOLDER)/libmlx.a

INCLUDES = -Iinclude -I$(LIBFT_FOLDER)/include -I$(MLX_FOLDER)
LDFLAGS = -L$(LIBFT_FOLDER)/lib -L$(MLX_FOLDER) -lft -lmlx -lXext -lX11 -lm

SRCS =	check.c\
		check1.c\
		draw.c\
		entity.c\
		event.c\
		free.c\
		init.c\
		main.c\
		utils.c
NAME = so_long

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	make -C $(LIBFT_FOLDER)

$(MLX):
	make -C $(MLX_FOLDER)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_FOLDER) clean
	make -C $(MLX_FOLDER) clean
	rm -f $(NAME)

fclean: clean
	make -C $(LIBFT_FOLDER) fclean

re: clean all