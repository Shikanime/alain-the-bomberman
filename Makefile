#
# Fluid
# Version: 1.5.7
#
# Use of this source code is governed by an MIT-style license that can be
# found in the LICENSE file at LICENSE
#

#
# CONFIGURATIONS
#

OUTNAME := bomberman

ROTDIR := .
DEPDIR := .cache
OBJDIR := .cache
OUTDIR := build
SRCDIR := src
HDRDIR := src

#
# DO NOT EDIT FORWARD
#

# Compilation settings

CC := gcc
TYPE := c

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-declarations -Wredundant-decls \
			-Winline -Wno-long-long -Wuninitialized -Wconversion -Wfatal-errors \
			-fsanitize=address

CFLAGS ?= -std=c11 $(WARNINGS)

# Options

ifeq ($(VERBOSE), 1)
    SILENCER :=
else
    SILENCER := @
endif

ifeq ($(DEBUG_BUILD), 1)
    CFLAGS +=-DDEBUG_BUILD -fsanitize=address -g
endif

# Compilation command

.PHONY: all
all: init $(OUTNAME)

.PHONY: exec
exec: $(OUTNAME)

.PHONY: dexec
dexec: $(OUTNAME)
	$(SILENCER)docker build -t $(OUTNAME) .
	$(SILENCER)docker run --rm -it -v "${PWD}":"/usr/src/priv" $(OUTNAME)

# Automated compilator

# Compilator files

ifeq ($(TEST_BUILD), 1)
    SRCS := $(shell find $(ROTDIR)/$(SRCDIR) -name "*.$(TYPE)" -type f | cut -sd / -f 3- | tr '\n' ' ')
else
    SRCS := $(shell find $(ROTDIR)/$(SRCDIR) ! -name '*.test.$(TYPE)' -name "*.$(TYPE)" -type f | cut -sd / -f 3- | tr '\n' ' ')
endif
OBJS := $(patsubst %, $(OBJDIR)/%, $(SRCS:$(TYPE)=o))
DEPS :=$(patsubst %.$(TYPE), %.d, $(SRCS))

# Compilation output configurations

CFLAGS += -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

$(OUTNAME): $(OBJS)
	$(SILENCER)$(CC) $(CFLAGS) -o $(OUTDIR)/$(OUTNAME) $^ -lSDL2 `sdl2-config --cflags --libs`

$(OBJDIR)/%.o: $(SRCDIR)/%.$(TYPE) $(DEPDIR)/%.d
	$(SILENCER)mkdir -p $(shell dirname $@)
	$(SILENCER)$(CC) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

# Helpers command

.PHONY: init
init:
	$(SILENCER)mkdir -p $(ROTDIR)/$(SRCDIR)
	$(SILENCER)mkdir -p $(ROTDIR)/$(OBJDIR)
	$(SILENCER)mkdir -p $(ROTDIR)/$(HDRDIR)
	$(SILENCER)mkdir -p $(ROTDIR)/$(OUTDIR)

.PHONY: clean
clean:
	$(SILENCER)$(RM) -r $(ROTDIR)/$(OBJDIR)
	$(SILENCER)mkdir -p $(ROTDIR)/$(OBJDIR)

.PHONY: fclean
fclean: clean
	$(SILENCER)$(RM) -r $(ROTDIR)/$(OUTDIR)
	$(SILENCER)mkdir -p $(ROTDIR)/$(OUTDIR)

.PHONY: re
re: fclean all

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
