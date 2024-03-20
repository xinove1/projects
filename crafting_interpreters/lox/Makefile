NAME=Lox
JFLAGS= -d . #-g
JCC=javac

compile:
	$(JCC) $(JFLAGS) *.java

run:
	java com.craftinginterpreters.lox.$(NAME)

e: $(compile)
	java com.craftinginterpreters.lox.$(NAME)

clean:
	$(RM) ./com/craftinginterpreters/lox/*.class
