# XiangQi
A XiangQi interface with AI player

# Comands List

- showc: shows all avaliable commands for user at the current program state

- play: starts a game (and sets players if the players are not set)

- set: goes to setting

- setl: sets language

- end: exits (at main menu) / return to the main manu (in game)

- back: returns to the privious state

- h: human player

- c[0-3]: computer player

- hint: requests a move hint (human only)

- m: makes a move (computer only)

- undo: undoes a move

# TODO List
- Get a better outcome function for Board

- Add an outcome function for Piece (from pos1 to pos2), other than the base value function

- Complete C3 and make it better again

- Optimize and simplify the code

- Comment [Interface/BoardGame/Player/IO].[h/cpp]

- Start considering GUI components

- Start working on BFS move searching (Hash function for the board)



---
Have fun!
