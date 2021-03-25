CC = gcc
CFLAGS = -Wall

#Linux-----------start
#SDL = -lm `sdl2-config --libs`
#LDFLAGS = $(SDL) -lSDL2 -lSDL2_mixer
#Linux-----------end

#Windows-----------start
INCLUDES = -I ../include
LIBS = -L ../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
#Windows-----------end
OBJDIR = ./objet
EXEC = ../bin/RGL

all: $(EXEC)

#Windows-----------start
../bin/RGL: ./objet/main.o ./objet/hud.o ./objet/sound.o ./objet/texture.o ./objet/salle.o ./objet/fonction_admin.o ./objet/perso.o ./objet/objet.o ./objet/porte.o ./objet/labyrinthe.o ./objet/actualisation.o ./objet/mob.o ./objet/menu.o ./objet/sauvegarde.o ./objet/combat.o ./objet/arme.o
	$(CC) -fstack-protector -g -o $@ $^ $(INCLUDES) $(LIBS)
#Windows-----------end

#Linux-----------start
#../bin/RGL: main.o salle.o fonction_admin.o perso.o objet.o porte.o labyrinthe.o actualisation.o mob.o menu.o sauvegarde.o combat.o arme.o
#	$(CC) -o $@ $^ $(LDFLAGS)
#Linux-----------end

#Pas nécessaire
main.o: labyrinthe.h perso.h mob.h actualisation.h fonction_admin.h menu.h porte.h sauvegarde.h combat.h hud.h sound.h super.h
salle.o: salle.h fonction_admin.h super.h							# DOXYGEN ACTUALISER
sound.o: sound.h fonction_admin.h super.h							# DOXYEGN FAIT
hud.o: hud.h fonction_admin.h super.h								# DOXYGEN FAIT
fonction_admin.o: fonction_admin.h super.h							# DOXYGEN FAIT
texture.o: texture.h fonction_admin.h super.h						# DOXYGEN FAIT
perso.o: perso.h fonction_admin.h salle.h arme.h super.h			# DOXYGEN FAIT
objet.o: objet.h fonction_admin.h super.h							# DOXYGEN ACTUALISER
porte.o: porte.h super.h											# DOXYGEN FAIT
labyrinthe.o: labyrinthe.h salle.h super.h							# DOCYGEN FAIT
actualisation.o: actualisation.h fonction_admin.h salle.h super.h	# DOXYGEN FAIT
mob.o: mob.h fonction_admin.h super.h								# DOXYGEN ACTUALISER
menu.o: menu.h fonction_admin.h sauvegarde.h texture.h super.h      # DOXYGEN ACTUALISER
sauvegarde.o: sauvegarde.h super.h									# DOXYGEN FAIT
combat.o: combat.h super.h											# DOXYGEN FAIT
arme.o: arme.h super.h												# DOXYGEN FAITvalg

#Windows-----------start
$(OBJDIR)%.o: %.c
	$(CC) -g -o $@ -c $< $(CFLAGS) $(INCLUDES) $(LIBS)
#Windows-----------end

#Linux-----------start
#%.o: %.c
#	$(CC) -o $@ -c $< $(LDFLAGS)
#Linux-----------end

#Windows-----------start
clean:
	del -rf ./objet
#Windows-----------end

#Linux-----------start
#clean: 
#	rm -rf *.o
#Linux-----------end

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

	

















