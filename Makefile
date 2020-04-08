NAME = ft_ls
SRCS_DIR = ./srcs
OBJS_PATH = objs
LIBFT_PATH = ./libft
LIBNAME = -lft
I_DIR = ./includes

CC = gcc
FLAGS = -Wall -Werror -Wextra
_SRCS = ft_ls.c \
		print.c \
		ft_ls_l.c \
		struct.c

SRCS = $(addprefix $(SRCS_DIR)/. $(_SRCS))
_OBJS = $(_SRCS:%.c=%.o)
OBJS = $(addprefix $(OBJS_PATH)/, $(_OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(OBJS) -o $(NAME) $(FLAGS) -L$(LIBFT_PATH) $(LIBNAME)


$(OBJS_PATH)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p objs
	@$(CC) -c -o $@ $< $(FLAGS) -I$(I_DIR) -I$(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) clean

re: fclean all

.PHONY: all clean fclean re
