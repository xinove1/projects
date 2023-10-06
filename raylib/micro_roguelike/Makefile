NAME= romicro

CC= gcc

CFLAGS= -fsanitize=address #-Wall -Wextra -Werror

RFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= main.c update.c render.c save_map.c utils.c path_finding.c breadth_first.c enemys.c

SRC_LIBFT= list.c

OBJ=$(SRC:.c=.o)

OBJ_LIBFT=$(SRC_LIBFT:.c=.o)

$(NAME): $(addprefix src/, $(SRC)) src/game.h
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC)) $(addprefix libft/, $(SRC_LIBFT))
	$(CC) $(OBJ) $(OBJ_LIBFT) $(CFLAGS) $(RFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
