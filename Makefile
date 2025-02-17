SRCS = mandatory/main.c mandatory/clean_and_exit.c mandatory/verify_cmds.c mandatory/helper_functions.c
SRCS_BNS = bonus/main_bonus.c bonus/verify_cmds_bonus.c bonus/helper_functions_bonus.c bonus/clean_and_exit_bonus.c \
	bonus/process_cmds_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BNS = $(SRCS_BNS:.c=.o)
NAME = pipex
NAME_BNS = pipex_bonus

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BNS)

$(NAME_BNS) : $(OBJS_BNS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_BNS) $(LIBFT) -o $(NAME_BNS)

$(LIBFT) :
	@$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BNS)
	@$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME) $(NAME_BNS)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean bonus