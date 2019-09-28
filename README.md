# Gomoku multiplayer
Gomoku multiplayer was created as semestral project for c++ course. It is implementation of Gomoku game (Piškvorky in Czech) except arbitrary number of human and AI players can play againts each other at once.

## Features
User can select:
* size of playing board
* number of players
* which players should be AI/humans
* starting player
* depth of minimax search

``` $ gomoku-multiplayer.exe
How big playing board do you want?: 10
How many players?: 3
Player 1 human or AI (h/a): h
Player 2 human or AI (h/a): a
Player 3 human or AI (h/a): a
Who do you want to start?: 1
How deep do you want to search game tree (d=3 is good default)?: 3
```

## Minimax vs Max-N
When only 2 players play against each other, vanilalla minimax with alpha-beta is used as AI algorithm. In game of 3 or more players, max-n algorithm is used (generalization of minimax for n players), but because search-tree cannot be pruned as easily as in minimax, it is much slower. In the current state, one evaluation of the whole board takes almost something like 0.5ms. Huge performance gain could be made by rewriting it more efficiently, hopefully in the future. Minimax performace could be further improved by implementing iterative deepening approach and by sorting moves properly. This is not being done yet.

## Controls
After executing the game, user is asked to input game parameters (from command-line), then the game starts. Clicking with left mouse button on a cell places player sign (X or O) there. When the game ends, another click anywhere restarts it with the same game parameters.

## How to compile on Windows with Visual Studio Code

1. Download [SFML 2.5.1] (https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip) & Extract SFML to **C:/SFML-2.5.1/** where the bin/lib/include folders are contained within
2. Download [GCC 7.3.0. MinGW (DW2) 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download) & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within
3. Download & Install Visual Studio Code if you don't already have it.
4. Install the official **C/C++** Extension, reload the window & wait for the dependencies to install.
5. Download & Install [Git Bash (for Windows)](https://git-scm.com/downloads)
6. Open the project folder in VS Code and ensure the **"terminal.integrated.shell.windows"** property in the project's **settings.json** is set to **bash.exe**'s correct location (default: C:/Program Files/Git/bin/bash.exe).
7. In **settings.json** Ensure **Path** in the **terminal.integrated.env.windows** object is set to the correct location of the compiler's executable (C:\\mingw32\\bin) and the SFML directory is correct as well. Keep in mind Paths should be separated by a semi-colon with no spaces between.
7.  At this point you should be able to build the project.


