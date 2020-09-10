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

CFORMAT := clang-format -i
CTIDY := clang-tidy --checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus-*

SOURCE_DIR := src
BIN_DIR := bin
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
OBJECTS := $(patsubst %.c, $(BIN_DIR)/%.o, $(SOURCES))
OUTFILE := $(BIN_DIR)/minesweeper

.PHONY: all lint precompile postcompile compile build clean run done
all: lint compile build run done


# Automatically create targets and gather their prerequisites
define create-ctarget
$1
> @echo -en "\e[37m[\e[34m?\e[37m]\e[0m $$< \e[36m⇒\e[0m $$@"
> @mkdir -p $$(dir $$@)
> @if $(CC) -o $$@ -c $(CFLAGS) $(CWARNINGS) $(CINCLUDES) $$<>/dev/null 2>&1;
> @then echo -e "\r\e[37m[\e[32m✓\e[37m]\e[0m";
> @else echo -e "\r\e[37m[\e[31m✗\e[37m]\e[0m";
> @$(CC) -o $$@ -c $(CFLAGS) $(CWARNINGS) $(CINCLUDES) $$<;
> @fi
endef

compile: precompile $(OBJECTS) postcompile
precompile:
> @echo -e "\e[1m\e[35mCOMPILING\e[0m"
postcompile:
> @echo -e "\e[94mDone compiling\e[0m\n"
$(foreach src,$(SOURCES),$(eval $(call create-ctarget,$(shell $(CC) -MM -MT $(patsubst %.c, $(BIN_DIR)/%.o, $(src)) $(src)))))


# Link and build outfile
build: $(OUTFILE)
$(OUTFILE): $(OBJECTS)
> @echo -e "\e[1m\e[35mLINKING\e[0m"
> @echo -en "\e[37m[\e[34m?\e[37m]\e[0m $^ \e[36m⇒\e[0m $@"
> @mkdir -p $(dir $@)
> @if $(CC) -o $@ $^ $(CLIBS)>/dev/null 2>&1;
> @then echo -e "\r\e[37m[\e[32m✓\e[37m]\e[0m";
> @else echo -e "\r\e[37m[\e[31m✗\e[37m]\e[0m";
> @$(CC) -o $@ $^ $(CLIBS);
> @fi
> @echo -e "\e[94mDone linking\e[0m\n"
done:
> @echo -e "\e[1m\e[48;5;28m\e[37mDone!\e[0m"


# Run out
run: $(OUTFILE)
> @$(OUTFILE)


# Create linter targets for source and header files
define create-linttarget
$1
> @echo -en "\e[37m[\e[34m?\e[37m]\e[0m $$<"
> @if ! $(CFORMAT) $$<>/dev/null 2>&1;
> @then echo -e "\r\e[37m[\e[31m✗\e[37m]\e[0m";
> @$(CFORMAT) $$<;
> @fi;
> @if $(CTIDY) $$<>/dev/null 2>&1;
> @then echo -e "\r\e[37m[\e[32m✓\e[37m]\e[0m";
> @else echo -e "\r\e[37m[\e[31m✗\e[37m]\e[0m";
> @$(CTIDY) $$<;
> @fi;
> @mkdir -p $$(dir $$@)
> @touch $$@
endef

$(foreach src,$(SOURCES),$(eval $(call create-linttarget,$(patsubst %.c, $(BIN_DIR)/%.cl, $(src)): $(src))))
$(foreach header,$(HEADERS),$(eval $(call create-linttarget,$(patsubst %.h, $(BIN_DIR)/%.hl, $(header)): $(header))))

prelint:
> @echo -e "\e[1m\e[35mLINTING\e[0m"
postlint:
> @echo -e "\e[94mDone linting\e[0m\n"
lint: prelint $(patsubst %.h, $(BIN_DIR)/%.hl, $(HEADERS)) $(patsubst %.c, $(BIN_DIR)/%.cl, $(SOURCES)) postlint


# Clean
clean:
> @rm -r $(BIN_DIR)
