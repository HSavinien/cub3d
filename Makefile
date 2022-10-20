SRCS	=	main.c

OBJS	=	${SRCS:%.c=%.o}

CC		=	gcc

MLXREP	=	library/mlx_macos

MLXCOMP	=	 -I ${MLXREP}	#42doc say it's a CFLAG, test say it's useless

MLXLNK	=	-L ${MLXREP} -lmlx -framework OpenGL -framework AppKit

CFLAGS	=	-Wall -Wextra -Werror -Ilibrary

LIB		=	-L./library/libft -lft ${MLXLNK}


NAME	=	cub3d

#rules    -------------------------------------------------------------    rules

all:		${NAME}

${NAME}: ${OBJS}
	make library
	@${CC} ${CFLAGS} ${LIB} ${OBJS} -o ${NAME}
	@echo "\033[1;32mcode compiled succesfully\033[0m"

library:	libft

libft:
	@make -s -C ./library/libft
	@echo "\033[1;33mlibft compiled\033[0m"

clean:
	@rm -rf ${OBJS} ${NAME}.dSYM ${BOBJS} test
	@make -s -C ./library/libft clean
	@echo "\033[1;31mobject files removed\033[0m"

fclean:		clean
	@rm -f ${NAME} generator bonus/checker
	@make -s -C ./library/libft fclean
	@echo "\033[1;33m${NAME} file removed\033[0m"

re:		fclean all

debug:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-debug -g

sanitize:	library
	@${CC} ${CFLAGS} ${LIB} ${SRCS} -o ${NAME}-sanitize -fsanitize=address

.PHONY:		all clean fclean re debug sanitize bonus
