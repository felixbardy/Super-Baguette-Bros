
# Système d'exploitation [Linux, MacOS]
OS = Linux

# Compilateur
CXX = g++
# Flags pour les compilations
CFLAGS = -ggdb -Wall -Wextra -std=c++17
# Flags pour l'édition des liens
LFLAGS = -ggdb -Wall -Wextra

LOCAL_INCLUDES = 	src 

#TODO Prévoir les cas pour Linux et MacOS -> Félix
LIB_INCLUDES = 

LIB_LINKS = 

CORE_SOURCES = src/core/Animation.cpp \
			   src/core/Entity.cpp \
			   src/core/Platform.cpp \
			   src/core/Player.cpp \
			   src/core/World.cpp

CORE_OBJECTS = obj/core/Animation.o \
			   obj/core/Entity.o \
			   obj/core/Platform.o \
			   obj/core/Player.o \
			   obj/core/World.o

#TODO Ajouter les autres sources

.PHONY: default all doc clean pentaclean core_test 

default: all

all: core_test doc


# * * * * * * * #
# *EXECUTABLES* #
# * * * * * * * #

# Règle de comfort
core_test: bin/core_test

# Génère l'exécutable de test du module 'core'
bin/core_test: $(CORE_OBJECTS) obj/core_test.o
	$(CXX) $(LFLAGS) -g $(CORE_OBJECTS) obj/core_test.o -o bin/core_test


# * * * * * * * * #
# *PATTERN RULES* #
# * * * * * * * * #

# S'applique à n'importe quel fichier source qui ne correspond pas aux règles plus bas
obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -I $(LOCAL_INCLUDES) $(LIB_INCLUDES) -c $< -o $@

# S'applique aux fichiers source du dossier core
obj/core/%.o: src/core/%.cpp
	$(CXX) $(CFLAGS) -I $(LOCAL_INCLUDES)  -c $< -o $@


# * * * * * * * * #
# *MISCELLEANOUS* #
# * * * * * * * * #

# Génère la documentation
doc:
	doxygen ./doc/Doxyfile

# Supprime les fichiers objet
clean:
	rm -rf obj/**.o

# Supprime les fichiers objets, les exécutables et la documentation
pentaclean: clean
	rm -rf doc/html doc/latex bin/*