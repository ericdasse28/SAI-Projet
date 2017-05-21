CC=gcc
LIB=-lglut -lGL -lGLU -lm
OBJETS=utilitaire.o

game: monde_snake.c
	$(CC) -o game monde_snake.c $(OBJETS) $(LIB)
	
utilitaire.o: utilitaire.c utilitaire.h

