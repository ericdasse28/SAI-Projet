CC=gcc
OPTIONS=-Wall
LIB=-lglut -lGL -lGLU

game: environnement.c
	$(CC) -o game environnement.c $(LIB) 
