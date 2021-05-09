
# MODULE IMAGE - GROUPE "LES BAGUETTES"

Cette archive est notre projet pour l'UE gestion de projet (LIFAP4).

Il s'agit d'un platformer (type de jeu vidéo similaire à Mario Bros)

On y joue un personnage très français capable de se déplacer, sauter
et récolter les pièces sur son chemin pour atteindre
la baguette en fin de niveau. \
Il possède un nombre limité de vie qu'il perd en tombant du niveau.

L'archive contient le code source du projet, les ressources nécéssaires à son exécution
ainsi qu'un makefile pour pouvoir le compiler et générer sa documentation.

Le projet est compilé à l'aide d'un Makefile fonctionnant sous Linux et MacOS.

## Installation

Ce projet utilise la librairie graphique [SDL2](https://www.libsdl.org/index.php) à installer au préalable via cette commande:

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
````

Ou sous MacOS avec Homebrew:

```bash
brew install sdl2 sdl2_image sdl2_ttf
```

## Compilation

*Si vous compilez sous MacOS*, changez la 1ère ligne du Makefile à: `OS = MacOS` \
Sinon aucune configuration ne devrait être requise. \
(Au besoin, les paramètres sont en début de fichier.)

Puis, pour compiler, placez vous à la racine du projet et tapez:

```sh
make
```

Cette commande compile la version graphique du jeu (la seule à jour). \
Plus d'options sont disponibles (voir la partie **_Makefile_** plus bas).

## Le Makefile

Le Makefile contient les règles pour générer les 3 exécutables et la documentation ainsi que des règles pratiques.
Les actions disponibles sont les suivantes:

* `default`: \
Génère la version graphique (`sdl_test`)

* `all`: \
Génère:
  * la version graphique du jeu (`sdl_test`)
  * l'exécutable de test (`core_test`)
  * la documentation (`doc`).

* `core_test`: \
Génère l'exécutable de test

* `sdl_test`: \
Génère l'exécutable de la version graphique du jeu

* `doc`: \
Génère la documentation en html à l'aide de Doxygen

* `clean`: \
Supprime les fichiers `.o` de `obj/`

* `pentaclean`: \
Supprime également les contenus de `bin` et `doc/` (sauf `image.doxy` et les contenus de `doc/img`)

## Développement

* **Félix Bardy**, L2 Info-Math \
mail: _felix.bardy@etu.univ-lyon1.fr_

* **Victoria Bekker**, L2 Info \
mail: _victoria.bekker@etu.univ-lyon1.fr_

* **Alexandre Dorier**, L2 Info \
mail: _alexandre.dorier@etu.univ-lyon1.fr_
