NAME=flecs.a

CC=gcc

CC_WINDOWS=x86_64-w64-mingw32-gcc

CFLAGS= -std=gnu99 -Dflecs_EXPORTS -DFLECS_SANITIZE \
		-DFLECS_CUSTOM_BUILD \
		-DFLECS_C \
		-DFLECS_MODULE \
		-DFLECS_PARSER \
		-DFLECS_PLECS \
		-DFLECS_RULES \
		-DFLECS_SNAPSHOT \
		-DFLECS_STATS \
		-DFLECS_MONITOR \
		-DFLECS_METRICS \
		-DFLECS_ALERTS \
		-DFLECS_SYSTEM \
		-DFLECS_PIPELINE \
		-DFLECS_TIMER \
		-DFLECS_META \
		-DFLECS_META_C \
		-DFLECS_UNITS \
		-DFLECS_EXPR \
		-DFLECS_JSON \
		-DFLECS_DOC \
		-DFLECS_COREDOC \
		-DFLECS_LOG \
		-DFLECS_APP \
		-DFLECS_OS_API_IMPL \
		#-DFLECS_CPP \
		-DFLECS_HTTP \
		-DFLECS_REST \
		-DFLECS_JOURNAL \

RM=rm -f

SRC= flecs.c

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) flecs.h
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

static: $(SRC) flecs.h
	$(CC) $(CFLAGS) -Dflecs_STATIC -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

windows: clean $(SRC) flecs.h
	$(CC_WINDOWS) $(CFLAGS) -Dflecs_STATIC -c $(SRC)
	x86_64-w64-mingw32-ar rc $(NAME) $(OBJ)
	x86_64-w64-mingw32-ranlib $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
