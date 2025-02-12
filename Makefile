SRCS = mandatory/main.c mandatory/clean_and_exit.c mandatory/verify_cmds.c mandatory/helper_functions.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
PRINTF = printf/ftprintf.a
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C libft

$(PRINTF) :
	@$(MAKE) -C printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@$(MAKE) -C printf clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C printf fclean

re: fclean all

.PHONY: all clean fclean re