# Hello!
### This is my 象棋 (Chinese Chess) program! Currently, it is a console application that provides a decent interface for Chinese Chess and some AI players implemented based on a backtracking move-searching algorithm. I have been optimizing it and I am planning to add features for program data handling. Further, I will develop another move-searching algorithm with bfs, which I have already had its outline on paper. Even further, I will be working on a nice GUI for the program.

#
## Build
To compile and build the program, please use the `makefile` or the bash shell script `build.sh` under `tools` directory. 

To see the usage of `build.sh`, please run 

```
tools/build.sh usage
```

By default, the compilation will give a program initially in Chinese, but you can run `build.sh` with `-le` to get a program in English, or alternatively, you can set it on the setting page in the program.



## Play

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

### Here is a list of commands:

- `showc`: show all avaliable commands for user at the current program state

- `showb`: display the board

- `play`: start a game (and start setting players if any players is not set)

- `set`: to setting

- `setl`: set language to another one (Chinese or English)

- `end`: exit (main page)  | stop the game and return to the main page (game)

- `back`: return to the previous page

- `hint`: request a hint (human player only)

- `m`: make a move (computer only)

- `undo`: undo a move

- `moves`: show all valid moves of the play at current round

### Players:

- `h`: human player

- `c[0-3]`: computer player [0-3]

### Demo

There is a demo for input and output, `demo1.in` and `demo1.out` in the demo directory. To view the demo output with coloured texts, please run
```
cat demo1.out
```

---

# TODO!!!

- Continue to optimize and simplify the code

- Get a better outcome function for Board to make C3 smarter

- get a efficient hash function for the board

- add functions that store program data locally and handle those data

- Start thinking of BFS move searching and GUI components





---
## Have fun!
