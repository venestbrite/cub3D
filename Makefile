SRCS = Mandatory/ft_bitmap.c \
	Mandatory/draw_floors.c \
	Mandatory/errors.c \
	Mandatory/ft_bzero.c \
	Mandatory/ft_memset.c \
	Mandatory/get_next_line_utils.c \
	Mandatory/get_next_line.c \
	Mandatory/init.c \
	Mandatory/main.c \
	Mandatory/movement.c \
	Mandatory/parser.c \
	Mandatory/render_extras.c \
	Mandatory/render_support_1.c \
	Mandatory/render.c \
	Mandatory/set_textures.c \
	Mandatory/sprites.c  \
	Mandatory/utils.c \
	Mandatory/left_right.c \
	Mandatory/keys.c \
	Mandatory/sort.c \
	Mandatory/utils_libft.c \
	Mandatory/colors_utils.c \
	Mandatory/parser_utils_1.c \
	Mandatory/parser_utils_2.c \
	Mandatory/parser_utils_3.c \
	Mandatory/parser_utils_4.c \
	Mandatory/map_finder.c \
	Mandatory/mouse_move.c \
	Mandatory/init_player.c 


OBJS			= $(SRCS:.c=.o)

SRCS_BONUS = Bonus/ft_bitmap.c \
	Bonus/draw_floors.c \
	Bonus/errors.c \
	Bonus/ft_bzero.c \
	Bonus/ft_memset.c \
	Bonus/get_next_line_utils.c \
	Bonus/get_next_line.c \
	Bonus/init.c \
	Bonus/main.c \
	Bonus/movement.c \
	Bonus/parser.c \
	Bonus/render_extras.c \
	Bonus/render_support_1.c \
	Bonus/render.c \
	Bonus/set_textures.c \
	Bonus/sprites.c  \
	Bonus/utils.c \
	Bonus/left_right.c \
	Bonus/keys.c \
	Bonus/sort.c \
	Bonus/utils_libft.c \
	Bonus/colors_utils.c \
	Bonus/parser_utils_1.c \
	Bonus/parser_utils_2.c \
	Bonus/parser_utils_3.c \
	Bonus/parser_utils_4.c \
	Bonus/map_finder.c \
	Bonus/mouse_move.c \
	Bonus/init_player.c 

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC				= gcc
RM				= rm -f

CFLAGS  = -Lmlx -lmlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror
NAME			= cub3D

%.o : %.c
	$(CC)  -c -o $@ $<

all:		compile_lib $(NAME)

$(NAME):		 $(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

welcome:
	bash welcome.sh


compile_lib:
	make -C ./mlx && cp ./mlx/libmlx.dylib ./

bonus:			$(OBJS_BONUS)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

clean:
				make clean -C ./mlx
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) rm libmlx.dylib

re:				clean all

.PHONY:			all clean fclean re bonus