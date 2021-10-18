# ncurses Minesweeper

Terminal game of Minesweeper, implemented in C with ncurses.

Minesweeper is a logic game where mines are hidden in a grid of squares. The
object is to open all the safe squares in the shortest time possible. Use
the arrow keys to move and &lt;SPACE&gt; to select. Read the Help page for more
information.

Click to watch a video demo on YouTube:
[![Minesweeper demo](http://img.youtube.com/vi/g7InqPoMShA/maxresdefault.jpg)](http://www.youtube.com/watch?v=g7InqPoMShA "Minesweeper demo")

## Compiling and Linking

Should be functional on all systems with an ncurses library. PDCurses may be
dropped in and linked on Windows, although this hasn't been tested. Might work
on WSL or Cygwin.

Requirements: `build-essential libncurses-dev`

Compiling and linking:
```
make compile build
```

**Binary executable deposited at `bin/minesweeper`.** You can copy this to
`/usr/local/bin/minesweeper` to run the game as `minesweeper` from any location
in your shell (given `/usr/local/bin` is in your path).

If you're contributing source code to this repository, install `clang-format
clang-tidy` and use `make` to target the linter programs. (`clang-format` is
a bit finicky; make sure you're running version 10.0.0 at least, or it will
yell at you about unsupported configuration in `.clang-format`.)

## Program structure

* Entry point at `src/main.c`
* State structs at `src/state.h`
* Rendering logic loop at `src/draw/draw.c`
* Game logic handler (input) at `src/game/game.c`
* Game renderer at `src/draw/game.c`

All header files correspond to a similarly named source file except
`src/draw/pages.h`, which encapsulates multiple sources in the same directory,
and `src/state.h`, which provides struct definitions for game state data.

## TODO

* Rewrite Options screen controls
* Rewrite game board renderer

## Copyright and Licensing

This package is copyrighted by [Joshua 'joshuas3'
Stockin](https://joshstock.in/) and licensed under the [MIT License](LICENSE).

A form of the following should be present in each source or header file.

```txt
ncurses-minesweeper Copyright (c) 2021 Joshua 'joshuas3' Stockin
<https://joshstock.in>
<https://git.joshstock.in/ncurses-minesweeper>

This software is licensed and distributed under the terms of the MIT License.
See the MIT License in the LICENSE file of this project's root folder.

This comment block and its contents, including this disclaimer, MUST be
preserved in all copies or distributions of this software's source.
```

&lt;<https://joshstock.in>&gt; | [josh@joshstock.in](mailto:josh@joshstock.in) | joshuas3#9641
