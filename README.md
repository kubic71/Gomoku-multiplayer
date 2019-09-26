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


