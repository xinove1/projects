NAME= 1bitrogue

MY_LIB= ../../mylibc

RAYLIB= ../../../raylib/src

FLECS= ./flecs

PARSON= ./parson

CC= gcc
CC_WINDOWS= x86_64-w64-mingw32-gcc

CFLAGS=  #-Wall -Wextra -Werror

DEBUG_FLAGS= -fsanitize=address -g

RFLAGS= -lGL -lm -lpthread -ldl -lrt -lX11
RFLAGS_WINDOWS= -lopengl32 -lgdi32 -lwinmm

WEBFLAGS = --preload-file assets -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=cwrap -s STACK_SIZE=1mb  -Os -s ASYNCIFY -s USE_GLFW=3 -DPLATFORM_WEB -sGL_ENABLE_GET_PROC_ADDRESS

RM= rm -f

SRC= main.c render.c update.c components.c map.c pathfinding.c utils.c raycast.c a_star.c load_levels.c

OBJ=$(SRC:.c=.o)

$(NAME): $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB)
	@make -C $(FLECS)
	@make -C $(PARSON)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(PARSON)/parson.a $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(CFLAGS) $(DEBUG_FLAGS) -lraylib $(RFLAGS) -o $(NAME)

static: $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB)
	@make -C $(FLECS) static
	@make -C $(PARSON)
	@make -C $(RAYLIB)
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(PARSON)/parson.a $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(RAYLIB)/libraylib.a $(CFLAGS) $(RFLAGS) -o $(NAME)

windows: $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(FLECS) windows
	@make -C $(MY_LIB) windows
	@make -C $(PARSON) windows
	@make -C $(RAYLIB) OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar
	$(CC_WINDOWS) -c $(addprefix src/, $(SRC))
	$(CC_WINDOWS) $(OBJ) $(PARSON)/parson.a $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(RAYLIB)/libraylib.a $(RFLAGS_WINDOWS) -o $(NAME).exe

web: $(addprefix src/, $(SRC)) src/components.h src/game.h
	make -C $(RAYLIB) PLATFORM=PLATFORM_WEB -B EMSDK_PATH=/home/xinove/stuff/emsdk  PYTHON_PATH=/usr/bin/python NODE_PATH=/home/xinove/stuff/emsdk/node/16.20.0_64bit/bin
	make -C $(FLECS) web
	make -C $(MY_LIB) web
	make -C $(PARSON) web
	emcc $(CFLAGS) -c $(addprefix src/, $(SRC))
	emcc $(OBJ)  $(PARSON)/parson.a $(MY_LIB)/mylib.a $(FLECS)/flecs.a $(RAYLIB)/libraylib.a -I$(RAYLIB) $(CFLAGS) $(RFLAGS) $(WEBFLAGS) -o $(NAME).html
#emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a  --shell-file path-to/shell.html

windows_test:  $(addprefix src/, $(SRC)) src/components.h src/game.h
	@make -C $(MY_LIB) windows
	@make -C $(FLECS) windows
	@make -C $(RAYLIB) OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar
	x86_64-w64-mingw32-gcc -c $(addprefix src/, $(SRC))
	x86_64-w64-mingw32-gcc $(OBJ) $(MY_LIB)/mylib.a $(FLECS)/flecs.a ../../../raylib/src/libraylib.a  -lopengl32 -lgdi32 -lwinmm -o $(NAME).exe

e: $(NAME)
	./$(NAME)

all: $(NAME)

clean:
	@make -C $(FLECS) clean
	@make -C $(MY_LIB) clean
	@make -C $(RAYLIB) clean
	@make -C $(PARSON) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(FLECS) fclean
	@make -C $(MY_LIB) fclean
	@make -C $(PARSON) fclean
	@make -C $(RAYLIB) clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
