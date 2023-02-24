SRCS	=	ft_isdigit.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_memset.c \
			ft_bzero.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_substr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_calloc.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_split.c \
			ft_strndup.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_reset_ptr.c \
			ft_isspace.c \
			ft_isupcase.c \
			ft_islowcase.c \
			ft_split_word.c \
			ft_memdup.c \
			get_next_line.c \
			get_next_line_utils.c \
			get_next_line_bonus.c \
			ft_char_in_set.c \
			ft_strcmp.c \
			ft_min_max.c \
			ft_atoi_base.c \
			
NB_SRCS	=	$(words $(SRCS))

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

#rules

all:		${NAME}

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

${NAME}:	${OBJS}
		@echo ""
		@cat .loading_bar
		@printf "\033[C✅\n"
		@echo "\033[1;32mcompiled\033[0m"
		@ar rcs ${NAME} ${OBJS}
		@ranlib ${NAME}
		@echo $$'\033[33mlibft compiled successfully'

clean:
		@rm -f ${OBJS} .loading_bar
		@echo $$'\033[31mremoving libft object files'

fclean:		clean
		@rm -f ${NAME}
		@echo $$'\033[31mremoving libft.a'

re:			fclean all

.PHONY:	all clean fclean re
