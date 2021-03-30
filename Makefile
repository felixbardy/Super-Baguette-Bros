
# Système d'exploitation [Linux, MacOS]
OS = Linux

# Compilateur
CXX = g++
# Flags pour les compilations
CFLAGS = -ggdb -Wall -std=c++17
# Flags pour l'édition des liens
LFLAGS = -ggdb -Wall

LOCAL_INCLUDES = 	src 

ifeq ($(OS), MacOS)
	LIB_INCLUDES = \
		-I/Library/Frameworks/SDL2.framework/Headers \
		-I/Library/Frameworks/SDL2_ttf.framework/Headers \
		-I/Library/Frameworks/SDL2_image.framework/Headers \
	
	LIB_LINKS = \
		-L/usr/local/lib \
		-lSDL2 \
		-lSDL2_image \
		-lSDL2_ttf
else
	ifeq ($(OS), Linux)
		LIB_INCLUDES = 

		LIB_LINKS = \
			-lSDL2 \
			-lSDL2_ttf \
			-lSDL2_image \
			-lSDL2_mixer
	endif
endif

CORE_SOURCES = src/core/Animation.cpp \
			   src/core/Entity.cpp \
			   src/core/Platform.cpp \
			   src/core/Player.cpp \
			   src/core/Segment.cpp \
			   src/core/World.cpp

CORE_OBJECTS = obj/core/Animation.o \
			   obj/core/Entity.o \
			   obj/core/Platform.o \
			   obj/core/Player.o \
			   obj/core/Segment.o \
			   obj/core/World.o

CONSOLE_SOURCES = src/console/ConsoleRenderer.cpp

CONSOLE_OBJECTS = obj/console/ConsoleRenderer.o

SDL_SOURCES = src/sdl/Renderer.cpp

SDL_OBJECTS = obj/sdl/Renderer.o


.PHONY: default all doc clean pentaclean core_test console_test sprite_test

default: all

all: core_test doc


# * * * * * * * #
# *EXECUTABLES* #
# * * * * * * * #

# Règle de comfort
core_test: bin/core_test

# Règle de comfort
console_test: bin/console_test

#Règle de comfort
sprite_test: bin/sprite_test

# Génère l'exécutable de test du module 'core'
bin/core_test: $(CORE_OBJECTS) obj/core_test.o
	$(CXX) $(LFLAGS) -g $(CORE_OBJECTS) obj/core_test.o -o bin/core_test

# Génère l'exécutable de test du module 'console'
bin/console_test: $(CORE_OBJECTS) $(CONSOLE_OBJECTS) obj/console_test.o
	$(CXX) $(LFLAGS) -g $(CORE_OBJECTS) $(CONSOLE_OBJECTS) obj/console_test.o -o bin/console_test

# Génère l'exécutable de test des sprites
bin/sprite_test: $(CORE_OBJECTS) $(SDL_OBJECTS) obj/sprite_test.o
	$(CXX) $(LFLAGS) $(LIB_LINKS) -g $(CORE_OBJECTS) $(SDL_OBJECTS) obj/sprite_test.o -o bin/sprite_test

# * * * * * * * * #
# *PATTERN RULES* #
# * * * * * * * * #

# S'applique à n'importe quel fichier source qui ne correspond pas aux règles plus bas
obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -I $(LOCAL_INCLUDES) $(LIB_INCLUDES) -c $< -o $@

# S'applique aux fichiers source du dossier core
obj/core/%.o: src/core/%.cpp
	$(CXX) $(CFLAGS) -I $(LOCAL_INCLUDES)  -c $< -o $@

# S'applique aux fichiers source du dossier sdl
obj/sdl/%.o: src/sdl/%.cpp
	$(CXX) $(CFLAGS) -I $(LOCAL_INCLUDES) $(LIB_INCLUDES) -c $< -o $@

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