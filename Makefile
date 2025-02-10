SRCS = mandatory/main.c mandatory/free_arr.c mandatory/clean_and_exit.c mandatory/verify_cmds.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f mandatory/*.o libft/*.o get_next_line/*.o

fclean: clean
	@rm -f $(NAME)
# @rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re