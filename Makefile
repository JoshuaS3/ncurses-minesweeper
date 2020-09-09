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


# Compiler settings
CC := gcc -std=c11
CFLAGS := -O3
CWARNINGS := -Werror -Wall -Wextra -pedantic
CINCLUDES := -Isrc
CLIBS := -lncurses
CLINT := --syntax-only

SOURCE_DIR := src
BIN_DIR := bin
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst %.c, $(BIN_DIR)/%.o, $(SOURCES))
OUTFILE := $(BIN_DIR)/minesweeper

.PHONY: all lint clean
all: $(OUTFILE)


# Automatically create targets and gather their prerequisites
define create-ctarget
$1
> @echo Compiling $$@ from $$^
> @mkdir -p $$(dir $$@)
> @$(CC) -o $$@ -c $(CFLAGS) $(CWARNINGS) $(CINCLUDES) $$<
endef

$(foreach src,$(SOURCES),$(eval $(call create-ctarget,$(shell $(CC) -MM -MT $(patsubst %.c, $(BIN_DIR)/%.o, $(src)) $(src)))))


# Build outfile
$(OUTFILE): $(OBJECTS)
> @echo Building $@ from $^
> @mkdir -p $(dir $@)
> $(CC) -o $@ $^ $(CLIBS)
> @echo Done!


# Lint
lint: $(SOURCES)
> @echo Linting...
> @$(foreach src,$^,$(CC) $(CLINT) $(CWARNINGS) $(CINCLUDES) $(src);)


# Clean
clean:
> @rm -r $(BIN_DIR)
