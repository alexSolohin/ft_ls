NAME = ft_ls
SRCS_DIR = src/
OBJ_PATH = obj/
LIBFT_PATH = libft/
I_DIR = includes/

CC = gcc
FLAGS = -Wall -Werror -Wextra
_SRSC = 

SRSC = $(addprefix $(SRCS_DIR)/. $(_SRCS))
_OBJS = $(_SRCS:%.c=%.o)
OBJS = $(addprefix $(OBJS_DIR)/, $(_OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(FLAGS) -L$(LIBFT_PATH)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) -c -o $@ $< $(FLAGS) -I$(I_DIR) -I$(LIBFT_PATH)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re