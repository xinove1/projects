NAME= so_long

LIBFT = ./libft

CC= gcc

CFLAGS= -Wall -Wextra -Werror
RFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= so_long.c errors.c parser.c utils.c clean.c movement.c

BONUS =

BONUS_OBJ = $(BONUS:.c=.o)

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) so_long.h
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a $(RFLAGS)  -o $(NAME)

all: $(NAME)

bonus: $(BONUS_OBJ)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: clean fclean
