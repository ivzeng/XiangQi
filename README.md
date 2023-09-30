# Hello!
### This is my 象棋 (Chinese Chess) program! Currently, it is a console application that provides a decent interface for Chinese Chess and some computer players based on a backtracking move-searching algorithm. So far, the interface part is complete and it supports many features such as board diplay, histroy, hint, and move-undo. I am working on the 5 computer players right now. Specifically, `Computer0`, `Computer1`, `Computer3`, and `computer4` use the basic move-searching algorithm with different depth, while  `Computer3` and `Computer4` may make random move, and `Computer4` has its data base that allows it to learn and improve. `Computer2` uses a difference outcome function that I will test it in the future.

#
## Build
To compile and build the program, please use the `makefile` or the bash shell script `build.sh` under `tools` directory. 

To see the usage of `build.sh`, please run 

```
tools/build.sh usage
```

By default, the compilation will give a program initially in Chinese, but you can run `build.sh` with `-le` to get a program in English, or alternatively, you can set it on the setting page in the program.



## Start a Game

When you execute the program, you will be in the main page. You can enter certain commands to do something. 

For example, 

to start a game with an ai as the red side and you as the black side, you can enter:
```
play c1 h
```
or
```
play
c2
h
```

to set the language, you can enter:
``` 
set setl back
```

to exit, simply enter

```
end
```

### Here is the list of commands:

- `showc`: show all avaliable commands for user at the current program state

- `showb`: display the board

- `play`: start a game (and start setting players if any players is not set)

- `train`: enter training mode

- `set`: to setting

- `setl`: set language to another one (Chinese or English)

- `end`: exit (main page)  | stop the game and return to the main page (game)

- `back`: return to the previous page

- `hint`: request a hint (human player only)

- `m`: make a move (computer only)

- `undo`: undo a move

- `moves`: show all valid moves of the play at current round

### and the list of players:

- `h`: human player

- `c[0-4]`: computer player [0-4]

### Training Mode
This mode will let two computer players player for a number of games. It is useful for training the database of the computer player.


An example to train Computer 4 with 10 games
```
train c4 c4 10
```

### Demo

There is a demo for input and output, `demo1.in` and `demo1.out` in the demo directory. To view the demo output with coloured texts, please run
```
cat demo1.out
```

---

# TODO!!!

- Continue to optimize and simplify the code

- Get a better outcome function for Board to make C2 smarter


## Changelogs

### 2023-03-17

#### Added
- Building Tools (`build.sh`)
  - `build.sh usage` to see the usage of `build.sh`
- Initial Language Options on Building
  - you can set the initial language of the program to English by running `build.sh -le` or `make PREPROCESSOR=-DINIT_LANGUAGE=2`

### 2023-03-24

#### Changed

- DFS Depth control
  - the weird stepping function is switched into a better and more clear function that recudes the depth by factoring with number of valid moves

### 2023-03-31

#### Added
- Debugging Option: 
  - to compile with enabled debugging mode, run `build.sh` with `-d` flag or `make` with `make "DEBUG=-DDEBUG -g"`


### 2023-05-03

#### Changed
- adjusted move analysis functions: `Player::dfsMovesAnalysis` now would calculate the expected payoff of each possible move and store the result in a vector of pair (payoff, move) called `movesEPayoff`, sorted in accending order of the payoff

- removed `XQBoard::outcome1` (the outcome function that analysizes the piece exchange outcome), renamed `XQBoard::outcome2` to `XQBoard::outcome1`

- simplified and optimized code in Player.cpp

### 2023-05-15

#### Added

- computer3, an variation of computer2 with ramdonization on move-selection

- (position) bounus matrix for each XQPiece for a better outcome funtion for XQBoard

#### Changed

- improved XQBoard::outcome and the related outcome function

- reduced the operation for computer2/3


### 2023-05-23

#### Added

- Computer 4
  - a computer player with all utilities of Computer 3 and the ability of using a database
- Database for Computer 4
- Training mode
  - allows two computer player to player for a number of games

#### Changed
- Text.h/cpp
  - slight changes on message


### 2023-09-30

#### Added

- builds of the program

#### Changed
- adjust the depth of searching algorithm for each player to ensure that they find a move in a reasonable time
- add a variable to tell the program about the environment


## Have fun!
