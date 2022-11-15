##
# Frogame Remake
#
# @file
# @version 0.1
NAME= frogame

LIBFT = ./../../libft

CC= gcc

CFLAGS= -Wall -Wextra -Werror -lraylib -g3 -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= main.c menus.c gameplay.c map_parser.c

OBJ=$(SRC:.c=.o)

$(NAME): $(addprefix src/, $(SRC)) src/frogame.h
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(LIBFT)/libft.a $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
