NAME	=	libftprintf.a

LIST	=	ft_printf.c				ft_printf_utils.c		ft_process_and_hex.c		ft_parsing.c\
			ft_printf_utils_1.c		ft_symbols.c			ft_digits.c

HEADER	=	ft_printf.h

OBJ		=	$(patsubst %.c, %.o, $(LIST))

FLAGS	=	-Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	ar rcs $(NAME) $?

%.o		:	%.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@
	
clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME) 

re		:	fclean all

.PHONY	: all clean fclean re