NAME= 1bitrogue

MY_LIB= ../../mylibc

RAYLIB= ../../../raylib/src

FLECS= ./flecs

CC= gcc
CC_WINDOWS= x86_64-w64-mingw32-gcc

CFLAGS= -fsanitize=address #-Wall -Wextra -Werror

RFLAGS= -lGL -lm -lpthread -ldl -lrt -lX11
RFLAGS_WINDOWS= -lopengl32 -lgdi32 -lwinmm

RM= rm -f

SRC= main.c render.c update.c components.c map.c pathfinding.c utils.c raycast.c

OBJ=$(SRC:.c=.o)

$(NAME): $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB)
	@make -C $(FLECS)
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(CFLAGS) -lraylib $(RFLAGS) -o $(NAME)

static: $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB)
	@make -C $(FLECS) static
	@make -C $(RAYLIB)
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(RAYLIB)/libraylib.a $(CFLAGS) $(RFLAGS) -o $(NAME)

windows: $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(FLECS) windows
	@make -C $(MY_LIB) windows
	@make -C $(RAYLIB) OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar
	$(CC_WINDOWS) -c $(addprefix src/, $(SRC))
	$(CC_WINDOWS) $(OBJ) $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(RAYLIB)/libraylib.a $(RFLAGS_WINDOWS) -o $(NAME).exe

windows_test:  $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB) windows
	@make -C $(FLECS) windows
	@make -C $(RAYLIB) OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar
	x86_64-w64-mingw32-gcc -c $(addprefix src/, $(SRC))
	x86_64-w64-mingw32-gcc $(OBJ) $(MY_LIB)/mylib.a $(FLECS)/flecs.a ../../../raylib/src/libraylib.a  -lopengl32 -lgdi32 -lwinmm -o $(NAME).exe

all: $(NAME)

clean:
	@make -C $(FLECS) clean
	@make -C $(MY_LIB) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(FLECS) fclean
	@make -C $(MY_LIB) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
