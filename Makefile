SRCS	=	cub3d.c \
			srcs/utils/error.c \
			srcs/utils/leaks_utils.c \
			srcs/utils/math.c \
			srcs/utils/mlx_images_utils.c \
			srcs/parsing/parsing.c \
			srcs/parsing/parsing_missing_data.c \
			srcs/parsing/parsing_read_color.c \
			srcs/parsing/parsing_readfile.c \
			srcs/parsing/parsing_utils.c \
			srcs/generals/main_loop.c \
			srcs/generals/collision.c \
			srcs/event/hook.c \
			srcs/event/hook_utils.c \
			srcs/event/key_event.c \
			srcs/bonus/draw_bonus.c \
			srcs/bonus/toogle_bonus.c \
			srcs/bonus/draw_minimap.c \
			srcs/bonus/minimap_utils.c \
			srcs/bonus/minimap_utils_2.c \
			srcs/fractol/new_fct.c \
			srcs/fractol/fractol.c \
			srcs/fractol/color.c \
			srcs/display/raycasting_main.c \
			srcs/display/get_next_pos.c \
			srcs/display/draw_wall.c \
			srcs/display/ray_utils.c \

OBJS	=	${SRCS:%.c=%.o}

NB_SRCS	=	$(words $(SRCS))

CC		=	gcc

MLXREP	=	library/mlx_macos

MLX		=	-L./${MLXREP} -lmlx -framework OpenGL -framework AppKit -MMD

CFLAGS	=	-Wall -Wextra -Werror -Ilibrary -I./ -I./${MLXREP}

LIB		=	-L./library/libft -lft ${MLX}

NAME	=	cub3D

#rules    -------------------------------------------------------------    rules

#standart rules

all:	${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1mcompiling\033[0m: $<                                 \n"
	@printf $$'\033[2m'
	@printf '%*s' $(NB_SRCS) '' | tr ' ' '*' #print one star per file in SRCS
	@printf $$'\033[0;1;33m|\033[0m⌛\r\033[0;1m'
	@cat .loading_bar 2>/dev/null || printf "" > .loading_bar
	@printf '*\r'
	@printf "\033[0m\033[A\r"
	@printf '*' >> .loading_bar

${NAME}: ${OBJS}
	@echo ""
	@printf '%*s' $(NB_SRCS) '' | tr ' ' '*' #print one star per file in SRCS
	@printf "\033[C✅\n"
	@echo "\033[1;32mcompiled\033[0m"
	@echo "\033[34mcompiling library :\033[0m"
	@make library
	@echo "\033[1;34mlinking files:\033[0m"
	@${CC} ${CFLAGS} ${LIB} ${OBJS} -o ${NAME}
	@rm -f .loading_bar
	@echo "✅ \033[1;32mcode compiled succesfully\033[0m ✅"

clean:
	@make -s -C ./library/libft clean
	@echo "\033[1;31mlibft cleaned\033[0m"
	@make -s -C ./library/mlx_macos clean
	@echo "\033[1;31mmlx cleaned\033[0m"
	@rm -rf ${OBJS} ${NAME}.dSYM ${BOBJS} test .loading_bar
	@echo "\033[1;31mobject files removed\033[0m"

fclean:		clean
	@make -s -C ./library/libft fclean
	@echo "\033[1;33mlibft.a file removed\033[0m"
	@rm -f ${NAME}
	@echo "\033[1;33m${NAME} file removed\033[0m"
	@rm -rf cub3d-*
	@echo "\033[1;33mdebug file removed\033[0m"

re:		fclean all

conf:
	@rm -f ${OBJS} ${BOBJS} ${NAME}
	@make

#library rules
library:	libft mlx

libft:
	@echo "\033[94mcompiling libft :\033[0m"
	@make -s -C ./library/libft
	@echo "\033[1;33mlibft compiled\033[0m\n"

mlx:
	@echo "\033[94mcompiling mlx :\033[0m"
	@make -C ./library/mlx_macos
	@echo "\033[1;33mminilibX compiled\033[0m"


#debug rules
debug:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-debug -g

sanitize:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-sanitize -g -fsanitize=address

#others rules

bonus: all

.PHONY:		all clean fclean re debug sanitize bonus
