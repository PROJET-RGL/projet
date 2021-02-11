CC = gcc
CFLAGS = -W -Wall
INCLUDES = -I ../include
LIBS = -L ../lib -lmingw32 -lSDL2main -lSDL2
EXEC = RGL

all: $(EXEC)

RGL: main.o salle.o fonction_admin.o perso.o objet.o porte.o structure.o labyrinthe.o actualisation.o mob.o menu.o option.o
	$(CC) -fstack-protector -o ../bin/$@ $^ $(INCLUDES) $(LIBS)

main.o: salle.h fonction_admin.h perso.h objet.h porte.h labyrinthe.h structure.h actualisation.h mob.h menu.h option.h
salle.o: salle.h fonction_admin.h structure.h porte.h objet.h mob.h
fonction_admin.o: fonction_admin.h
perso.o: perso.h fonction_admin.h salle.h structure.h
objet.o: objet.h perso.h fonction_admin.h salle.h structure.h
porte.o: porte.h structure.h
structure.o: structure.h
labyrinthe.o: labyrinthe.h perso.h fonction_admin.h salle.h objet.h mob.h structure.h
actualisation.o: actualisation.h perso.h fonction_admin.h salle.h structure.h porte.h
mob.o: mob.h fonction_admin.h structure.h
menu.o: menu.h option.h fonction_admin.h 
option.o: option.h menu.h fonction_admin.h

%.o: %.c
	$(CC) -o $@ -c $< $(INCLUDES) $(LIBS)

clean:
	del -rf *.o