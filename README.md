# ncurses Minesweeper

Terminal game of Minesweeper, implemented in C with ncurses.

## Game

Minesweeper is a logic game where mines are hidden in a grid of squares. The
object is to open all the safe squares in the shortest time possible. Use
\<hjkl\> to move and \<SPACE\> to select. Read the Help page for more
information.

![Title screen](https://i.imgur.com/HRhl4B2.png)
![Ready to start](https://i.imgur.com/HObmgcl.png)
![Playing](https://i.imgur.com/7Wx2mbk.png)
![Kaboom](https://i.imgur.com/T6bjZVK.png)
![Finished game](https://i.imgur.com/8c6zKGl.png)

## Installation

Currently functional on all systems with an ncurses library. PDCurses may be
dropped in and linked on Windows, although this hasn't been tested.

Requirements: `build-essential libncurses-dev`

Compiling and linking:
```
make compile build
```

Binary executable deposited at `bin/minesweeper`.

**If you're contributing source code to this repository, install `clang-format
clang-tidy` and use `make` to target the linter programs.** (`clang-format` is
a bit finicky; make sure you're running version 10.0.0, or it will yell at you
about unsupported configuration in `.clang-format`.)

## Source file structure and program flow

* Entry point at `src/main.c`
* Rendering logic loop at `src/draw/draw.c`
* Game logic handler at `src/game/game.c`
* Game renderer at `src/draw/game.c`

All header files correspond to a similarly named source file except
`src/draw/pages.h` which encapsulates multiple sources in the same directory.

# Copyright and Licensing

This package is copyrighted by [Joshua 'joshuas3'
Stockin](https://joshstock.in/) and licensed under the [MIT License](LICENSE).

A form of the following should be present in each source or header file.

```txt
ncurses-minesweeper Copyright (c) 2020 Joshua 'joshuas3' Stockin
<https://joshstock.in>
<https://github.com/JoshuaS3/ncurses-minesweeper>
This software is licensed under the MIT License.
```

<<https://joshstock.in>> | joshstockin@gmail.com | joshuas3#9641 |
[LinkedIn](https://www.linkedin.com/in/joshstockin/)
