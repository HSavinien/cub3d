<<<<<<< HEAD
SRCS	=	cub3d.c \
			srcs/utils/error.c \
			srcs/utils/leaks_utils.c \
			srcs/utils/mlx_images_utils.c \
			srcs/parsing/parsing.c \
			srcs/parsing/parsing_missing_data.c \
			srcs/parsing/parsing_read_color.c \
			srcs/parsing/parsing_readfile.c \
			srcs/parsing/parsing_utils.c \
			srcs/generals/main_loop.c \
			srcs/event/hook.c \
			srcs/bonus/draw_minimap.c \
			srcs/display/ray_utils.c \
			tmp/debug.c \

OBJS	=	${SRCS:%.c=%.o}

CC		=	gcc

MLXREP	=	library/mlx_macos

MLX		=	-L./${MLXREP} -lmlx -framework OpenGL -framework AppKit -MMD

CFLAGS	=	-Wall -Wextra -Werror -Ilibrary -I./ -I./${MLXREP}

LIB		=	-L./library/libft -lft ${MLX}


NAME	=	cub3d

#rules    -------------------------------------------------------------    rules

#standart rules

all:		${NAME}

${NAME}: ${OBJS}
	@echo "\033[34mcompiling library :\033[0m"
	@make library
	@echo "\033[1;34mlinking files:\033[0m"
	@${CC} ${CFLAGS} ${LIB} ${OBJS} -o ${NAME}
	@echo "\033[1;32mcode compiled succesfully\033[0m"

clean:
	@make -s -C ./library/libft clean
	@echo "\033[1;31mlibft cleaned\033[0m"
	@make -s -C ./library/mlx_macos clean
	@echo "\033[1;31mmlx cleaned\033[0m"
	@rm -rf ${OBJS} ${NAME}.dSYM ${BOBJS} test
	@echo "\033[1;31mobject files removed\033[0m"

fclean:		clean
	@make -s -C ./library/libft fclean
	@echo "\033[1;33mlibft.a file removed\033[0m"
	@rm -f ${NAME}
	@echo "\033[1;33m${NAME} file removed\033[0m"
	rm -rf cub3d-*
	@echo "\033[1;33mdebug file removed\033[0m"

re:		fclean all

#library rules
library:	mlx libft

libft:
	@echo "\033[94mcompiling libft :\033[0m"
	@make -C ./library/libft
	@echo "\033[1;33mlibft compiled\033[0m"

mlx:
	@echo "\033[94mcompiling mlx :\033[0m"
	@make -C ./library/mlx_macos
	@echo "\033[1;33mminilibX compiled\033[0m"


#dubug rules
debug:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-debug -g

sanitize:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-sanitize -g -fsanitize=address

#others rules

.PHONY:		all clean fclean re debug sanitize bonus
