LINUX = no
CC = gcc
CFLAGS = -Wall
EXEC = ../bin/RGL
#SRC = $(wildcard *.c)
#OBJ = $(SRC:.c=.o)
OBJDIR = objet/

ifeq ($(LINUX), no)

INCLUDES = -I ../include
LIBS = -L ../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

else

SDL = -lm `sdl2-config --libs`
LDFLAGS = $(SDL) -lSDL2 -lSDL2_mixer

endif

all: $(EXEC)

ifeq ($(LINUX), no)

../bin/RGL: $(OBJDIR)main.o $(OBJDIR)hud.o $(OBJDIR)sound.o $(OBJDIR)texture.o $(OBJDIR)salle.o $(OBJDIR)fonction_admin.o $(OBJDIR)perso.o $(OBJDIR)objet.o $(OBJDIR)porte.o $(OBJDIR)labyrinthe.o $(OBJDIR)actualisation.o $(OBJDIR)mob.o $(OBJDIR)menu.o $(OBJDIR)sauvegarde.o $(OBJDIR)combat.o $(OBJDIR)item.o
	$(CC) -fstack-protector -g -o $@ $^ $(INCLUDES) $(LIBS)

$(OBJDIR)%.o: %.c
	$(CC) -g -o $@ -c $< $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	del .\objet\*.o

else

../bin/RGL: $(OBJDIR)main.o $(OBJDIR)hud.o $(OBJDIR)sound.o $(OBJDIR)texture.o $(OBJDIR)salle.o $(OBJDIR)fonction_admin.o $(OBJDIR)perso.o $(OBJDIR)objet.o $(OBJDIR)porte.o $(OBJDIR)labyrinthe.o $(OBJDIR)actualisation.o $(OBJDIR)mob.o $(OBJDIR)menu.o $(OBJDIR)sauvegarde.o $(OBJDIR)combat.o $(OBJDIR)arme.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(LDFLAGS)

clean:
	@rm -rf *.o

endif

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

















