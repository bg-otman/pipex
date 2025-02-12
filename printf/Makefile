SRCS = ft_putchar.c ft_check_specifier.c ft_strlen.c ft_printf.c ft_valid_specifier.c ft_putstr.c ft_putnbr.c \
		ft_puthex.c ft_putunsint.c ft_putadresse.c
OBJECTS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
NAME = ftprintf.a

all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJECTS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
