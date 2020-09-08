# Preamble >> Make config
SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

all: bin/main


# Compiler settings
CC := gcc -std=c11
CFLAGS := -O3
CWARNINGS := -Werror -Wall -Wextra -pedantic
CINCLUDES := -Isrc/
CLIBS := -lncurses
CLINT := --syntax-only


# File dependencies
bin/main.o: src/main.c
> @echo Compiling $@ from $<
> $(CC) -o $@ -c $(CFLAGS) $(CWARNINGS) $< $(CINCLUDES)


# Binary dependencies
bin/main: bin/main.o
> @echo Compiling $@ from $^
> $(CC) -o $@ $^ $(CLIBS)
> @echo Done!
