CC = gcc
CFLAGS = -W -Wall  #windows
#CFLAGS = -Wall   #linux

#Linux-----------start
#SDL = -ldl `sdl2-config --libs`
#LDFLAGS = $(SDL) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2_mixer
#Linux-----------end

INCLUDES = -I ../include
LIBS = -L ../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
EXEC = ../bin/RGL

all: $(EXEC)

../bin/RGL: main.o salle.o fonction_admin.o perso.o objet.o porte.o labyrinthe.o actualisation.o mob.o menu.o sauvegarde.o combat.o arme.o
	$(CC) -fstack-protector -o $@ $^ $(INCLUDES) $(LIBS)

#version Linux_________________

#../bin/RGL: main.o salle.o fonction_admin.o perso.o objet.o porte.o labyrinthe.o actualisation.o mob.o menu.o 
#	$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBS) -o $@


#-------------ancienne version pour compiler le prog----------------- 
#bin/prog: obj/main.o obj/salle.o [...] obj/jeu.o
#	gcc obj/main.o obj/salle.o [...] obj/jeu.o $(LDFLAGS) -o bin/prog


main.o: labyrinthe.h perso.h mob.h actualisation.h fonction_admin.h menu.h porte.h sauvegarde.h combat.h super.h
salle.o: salle.h fonction_admin.h super.h
fonction_admin.o: fonction_admin.h super.h
perso.o: perso.h fonction_admin.h salle.h arme.h super.h
objet.o: objet.h fonction_admin.h super.h
porte.o: porte.h super.h
labyrinthe.o: labyrinthe.h salle.h super.h
actualisation.o: actualisation.h fonction_admin.h salle.h super.h
mob.o: mob.h fonction_admin.h super.h
menu.o: menu.h fonction_admin.h super.h sauvegarde.h
sauvegarde.o: sauvegarde.h super.h
combat.o: combat.h super.h
arme.o: arme.h super.h

%.o: %.c
	$(CC) -o $@ -c $<     $(INCLUDES) $(LIBS)


#Version linux_________

#-------------ancienne version pour un objet----------------- 
#obj/main.o: src/main.c
#	gcc -Wall src/main.c -c `sdl2-config --cflags` -o obj/main.o

#règle générique
#%.o: %.c
#	$(CC) $(CFLAGS) $< -c  `sdl2-config --cflags` -o $@



clean:
	del -rf *.o


#####
#       %.o : %.c     règle générique pour construire un .o à partir d'un .c
#
#       $@      Le nom de la cible
#
#       $<      Le nom de la première dépendance
#
#       $^      La liste des dépendances
#
#       $?      La liste des dépendances plus récentes que la cible
#
#       $*      Le nom du fichier sans suffixe
#####

	

















