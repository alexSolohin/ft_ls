NAME		:=	ft_ls
DIR_SRC		:=	srcs/
DIR_BIN		:=	bin/
DIR_INCLUDE :=	include/
CC			:=	gcc
CFLAGS		:=	-g -Wextra -Werror -Wall
HEADERS		:=	libft.h ft_printf.h ft_getopt.h ft_ls.h
LIBFT		:=	libft.a
SRC			:=	main.c collect_flags.c ft_getopt.c ft_getopt_long.c ft_ls.c \
				sort_list.c tools.c utils.c color_file.c print_output.c \

OBJS 		:= $(SRC:.c=.o)
LIBFT		:= $(addprefix $(DIR_SRC), $(LIBFT))

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(DIR_BIN), $(OBJS)) $(LIBFT) -o $@

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(CFLAGS) $< -o $(DIR_BIN)$@ -I $(DIR_INCLUDE)

$(DIR_BIN):
	mkdir -p $@

clean:
	rm -rf $(addprefix $(DIR_BIN), $(OBJS))
	rm -rf $(DIR_BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) clean fclean re