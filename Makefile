NAME	=	fdf

LIST	=	draw.c	main.c	until.c	control.c	read_file.c	until1.c

HEDEAR	=	FDF.h

GCC		=	gcc -Wall -Wextra -Werror

OBJ		=	$(patsubst %.c, %.o, $(LIST))

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	@$(MAKE) -C ./libft
	$(GCC) $(LIST) ./libft/libft.a ./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)

clean		:
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJ)

fclean		:	clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re